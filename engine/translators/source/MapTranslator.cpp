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

DisplayMap MapTranslator::create_display_map(const MapPtr& map, const MapPtr& fov_map, const MapDisplayArea& display_area, const Coordinate& reference_coords, const bool full_redraw_required)
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
  // required.
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
    Coordinate display_coords = CreatureCoordinateCalculator::calculate_display_coordinate(display_area, map, reference_coords);

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

      DisplayTile display_tile = translate_coordinate_into_display_tile(map, fov_map, actual_row, actual_col);

      // Set the cursor coordinates
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
DisplayTile MapTranslator::translate_coordinate_into_display_tile(const MapPtr& map, const MapPtr& fov_map, const int actual_row, const int actual_col)
{
  // Get the map tile
  TilePtr map_tile = map->at(actual_row, actual_col);
      
  // Check to see if a corresponding FOV tile exists
  TilePtr fov_map_tile = fov_map->at(actual_row, actual_col);

  // Translate the map tile
  return create_display_tile(map_tile, fov_map_tile);
}

DisplayTile MapTranslator::create_display_tile(const TilePtr& actual_tile, const TilePtr& fov_tile)
{
  DisplayTile display_tile;

  if (fov_tile)
  {
    CreaturePtr creature = actual_tile->get_creature();
    Inventory& inv = actual_tile->get_items();
    FeaturePtr feature = actual_tile->get_feature();

    if (creature) // If a creature exists on this tile - will be null if the ptr is not init'd
    {
      display_tile = create_display_tile_from_creature(creature);
    }
    else if (!inv.empty()) // If at least one item exists in the tile's inventory of items
    {
      ItemPtr item = inv.at(0); // Get the first item
      display_tile = create_display_tile_from_item(item);
    }
    else if (feature) // There's no creature, and no items.  Is there a feature?
    {
      display_tile = create_display_tile_from_feature(feature);
    }
    else // Nothing else - display the tile.
    {
      display_tile = create_display_tile_from_tile(actual_tile);
    }      
  }
  else
  {
    if (actual_tile->get_explored())
    {
      display_tile = create_unseen_and_explored_display_tile(actual_tile);
    }
    else
    {
      if (actual_tile->get_viewed())
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
  display_tile.set_colour(COLOUR_BLACK);
  
  return display_tile;  
}
