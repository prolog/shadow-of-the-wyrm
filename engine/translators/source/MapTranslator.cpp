#include <algorithm>
#include "common.hpp"
#include "CreatureCoordinateCalculator.hpp"
#include "Display.hpp"
#include "Game.hpp"
#include "MapDisplayArea.hpp"
#include "MapTranslator.hpp"

using namespace std;

MapTranslator::MapTranslator()
{
}

MapTranslator::~MapTranslator()
{
}

DisplayMap MapTranslator::create_display_map(const bool player_blinded, const MapPtr& map, const MapPtr& fov_map, const MapDisplayArea& display_area, const Coordinate& reference_coords, const bool full_redraw_required)
{
  Coordinate display_coords = CreatureCoordinateCalculator::calculate_display_coordinate(display_area, map, reference_coords);
  
  int actual_row, actual_col;

  // Get the current season and set it into the copy.
  // I believe this is what people call "a train wreck":
  Season season = Game::instance().get_current_world()->get_calendar().get_season()->get_season();

  DisplayMap display_map(display_area.get_height(), display_area.get_width());

  int cursor_row = reference_coords.first;
  int cursor_col = reference_coords.second;
  Coordinate engine_coord = CreatureCoordinateCalculator::calculate_engine_coordinate(display_area, map, reference_coords);

  uint start_y, start_x;
  uint stop_y, stop_x;
  int display_height = display_area.get_height();
  int display_width = display_area.get_width();

  // Set the loop's start/stop points based on whether a full redraw is
  // required.  It may have been required as part of the display coordinate
  // calculations done as part of this function!
  if (full_redraw_required)
  {
    // We can use the full display, so go from 0 to display_height/display_width.
    start_y = 0;
    stop_y = display_height;
    start_x = 0;
    stop_x = display_width;
  }
  else
  {
    start_y = std::max<int>(0, display_coords.first - CreatureConstants::DEFAULT_CREATURE_LINE_OF_SIGHT_LENGTH - 1);
    stop_y = std::min<int>(display_height, display_coords.first + CreatureConstants::DEFAULT_CREATURE_LINE_OF_SIGHT_LENGTH + 2);
    start_x = std::max<int>(0, display_coords.second - CreatureConstants::DEFAULT_CREATURE_LINE_OF_SIGHT_LENGTH - 1);
    stop_x = std::min<int>(display_width, display_coords.second + CreatureConstants::DEFAULT_CREATURE_LINE_OF_SIGHT_LENGTH + 2);
  }

  for (uint d_row = start_y; d_row < stop_y; d_row++)
  {
    for (uint d_col = start_x; d_col < stop_x; d_col++)
    {
      // Create the display coordinate.  Note that this can be different
      // from the actual engine coordinate!
      //
      // E.g, if the player is at 90, 30
      // and the display is 80x20
      //
      // The display's (col 0, row 0) will start at 80, 20 on the real
      // map, and the player will be at 10, 10 relative to this.
      Coordinate display_coords(d_row, d_col);

      actual_row = engine_coord.first + d_row;
      actual_col = engine_coord.second + d_col;

      DisplayTile display_tile = translate_coordinate_into_display_tile(player_blinded, map, fov_map, actual_row, actual_col);

      // Set the cursor coordinates.  Update the game's tracked display
      // coordinates, so that a full redraw can be performed.
      if ((actual_row == cursor_row) && (actual_col == cursor_col))
      {
        display_map.set_cursor_coordinate(display_coords);
      }

      display_tile.set_season(season);

      // Set the display tile
      display_map.set(display_coords, display_tile);
    }
  }

  return display_map;
}

// Create a display tile from a given coordinate, given the current map
// and the current FOV map.
DisplayTile MapTranslator::translate_coordinate_into_display_tile(const bool player_blinded, const MapPtr& map, const MapPtr& fov_map, const int actual_row, const int actual_col)
{
  // Get the map tile
  TilePtr map_tile = map->at(actual_row, actual_col);
      
  // Check to see if a corresponding FOV tile exists
  TilePtr fov_map_tile = fov_map->at(actual_row, actual_col);

  // Translate the map tile
  return create_display_tile(player_blinded, map_tile, fov_map_tile);
}

// Create the tile to display, based on the tile's properties, and whether or
// not the player's been blinded.  If the player's been blinded, the tile will
// be black, unless it is the player's tile, in which case the player will be
// displayed.
DisplayTile MapTranslator::create_display_tile(const bool player_blinded, const TilePtr& actual_tile, const TilePtr& fov_tile)
{
  DisplayTile display_tile;

  // Is it a FOV tile, and is the player not blinded?
  // Special case for blindness - does the tile contain the player?  Because
  // we always want to show the player.
  if ((fov_tile && !player_blinded) || (player_blinded && fov_tile && fov_tile->get_creature() && fov_tile->get_creature()->get_is_player()))
  {
    CreaturePtr creature = actual_tile->get_creature();
    IInventoryPtr inv = actual_tile->get_items();
    FeaturePtr feature = actual_tile->get_feature();

    // If a creature exists on this tile - will be null if the ptr is not init'd.
    // Display the creature if the player is not blind, or if the player is the
    // creature (presumably, the player always has a sense of where they are!).
    if (creature)
    {
      display_tile = create_display_tile_from_creature(creature);
    }
    else if (!inv->empty() && !player_blinded) // If at least one item exists in the tile's inventory of items
    {
      ItemPtr item = inv->at(0); // Get the first item
      display_tile = create_display_tile_from_item(item);
    }
    else if (feature && !feature->get_is_hidden() && !player_blinded) // There's no creature, and no items.  Is there a feature?  Can it be seen?
    {
      display_tile = create_display_tile_from_feature(feature);
    }
    else // Nothing else, or the player is blind - display the tile only.
    {
      display_tile = create_display_tile_from_tile(actual_tile);
    }      
  }
  else
  {
    if (actual_tile->get_explored() && !player_blinded)
    {
      display_tile = create_unseen_and_explored_display_tile(actual_tile);
    }
    else
    {
      if (actual_tile->get_viewed() && !player_blinded)
      {
        display_tile = create_unseen_and_previously_viewed_display_tile(actual_tile);          
      }
      else
      {
        display_tile = create_unseen_and_unexplored_display_tile();
      }
    }
  }

  return display_tile;
}

// Create a display tile from a given creature
DisplayTile MapTranslator::create_display_tile_from_creature(const CreaturePtr& creature)
{
  return create_display_tile_from_symbol_and_colour(creature->get_symbol(), creature->get_colour());
}

// Create a display tile from a given tile feature
DisplayTile MapTranslator::create_display_tile_from_feature(const FeaturePtr& feature)
{
  return create_display_tile_from_symbol_and_colour(feature->get_symbol(), feature->get_colour());
}

// Create a display tile from a given item
DisplayTile MapTranslator::create_display_tile_from_item(const ItemPtr& item)
{
  return create_display_tile_from_symbol_and_colour(item->get_symbol(), item->get_colour());
  DisplayTile empty;
  return empty;
}

// Create a display tile from a given tile
DisplayTile MapTranslator::create_display_tile_from_tile(const TilePtr& tile)
{
  DisplayTile display_tile;
  Game& game = Game::instance();

  // Make a copy of the prototype tile off the game.
  vector<DisplayTile> tiles_info = game.get_tile_display_info_ref();
  DisplayTile tile_info = tiles_info.at(tile->get_tile_type());
  display_tile = tile_info;

  size_t foo = display_tile.get_colours().size();

  return display_tile;
}

DisplayTile MapTranslator::create_display_tile_from_symbol_and_colour(const uchar symbol, const Colour colour)
{
  DisplayTile display_tile(symbol, colour);
  
  return display_tile;  
}

DisplayTile MapTranslator::create_unseen_and_previously_viewed_display_tile(const TilePtr& tile)
{
  // JCD FIXME LATER
  return create_unseen_and_explored_display_tile(tile);
}

DisplayTile MapTranslator::create_unseen_and_explored_display_tile(const TilePtr& tile)
{
  DisplayTile display_tile;
  
  display_tile = create_display_tile_from_tile(tile);
  
  return display_tile;
}

DisplayTile MapTranslator::create_unseen_and_unexplored_display_tile()
{
  DisplayTile display_tile;
  
  display_tile.set_symbol(' ');
  display_tile.set_colour(Colour::COLOUR_BLACK);
  
  return display_tile;  
}
