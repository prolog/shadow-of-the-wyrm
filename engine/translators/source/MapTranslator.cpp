#include <algorithm>
#include "common.hpp"
#include "Display.hpp"
#include "Game.hpp"
#include "MapTranslator.hpp"

using namespace std;

MapTranslator::MapTranslator()
{
}

MapTranslator::~MapTranslator()
{
}

DisplayMap MapTranslator::create_display_map(const MapPtr& map, const MapPtr& fov_map, const MapDisplayArea& display_area, const Coordinate& reference_coords)
{
  uint display_width = display_area.get_width();
  uint display_height = display_area.get_height();

  Dimensions d = map->size();
  int map_height = d.get_y();
  int map_width  = d.get_x();

  DisplayMap display_map;

  int cursor_row = reference_coords.first;
  int cursor_col = reference_coords.second;

  // Ignore the decimal part - we only care about the int part.
  int engine_map_start_row = std::min(map_height - display_height, ((int)(cursor_row / display_height)) * display_height);
  int engine_map_start_col = std::min(map_width - display_width, ((int)(cursor_col / display_width)) * display_width);
  
  int actual_row, actual_col;

  for (uint d_row = 0; d_row < display_height; d_row++)
  {
    for (uint d_col = 0; d_col < display_width; d_col++)
    {
      // Create the display coordinate.  Note that this can be different
      // from the actual engine coordinate!
      //
      // E.g, if the player is at 90, 30
      // and the display is 80x20
      //
      // The display's (col 0, row 0) will start at 80, 20 on the real
      // map, and the player will be at 10, 10 relative to this.
      Coordinate display_coords;
      display_coords.first = d_row;
      display_coords.second = d_col;

      actual_row = engine_map_start_row+d_row;
      actual_col = engine_map_start_col+d_col;

      // Get the map tile
      TilePtr map_tile = map->at(actual_row, actual_col);
      
      // Check to see if a corresponding FOV tile exists
      TilePtr fov_map_tile = fov_map->at(actual_row, actual_col);

      // Translate the map tile
      DisplayTile display_tile = create_display_tile(map_tile, fov_map_tile);

      // Set the cursor coordinates
      if ((actual_row == cursor_row) && (actual_col == cursor_col))
      {
        display_map.set_cursor_coordinate(display_coords);
      }

      // Set the display tile
      display_map.set(display_coords, display_tile);
    }
  }

  return display_map;
}

DisplayTile MapTranslator::create_display_tile(const TilePtr& actual_tile, const TilePtr& fov_tile)
{
  DisplayTile display_tile;

  Game* game_info = Game::instance();

  if (game_info)
  {
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
  Game* game_info = Game::instance();

  if (game_info)
  {
    vector<DisplayTile> tiles_info = game_info->get_tile_display_info_ref();
    DisplayTile tile_info = tiles_info.at(tile->get_tile_type());
    display_tile = tile_info;    
  }
  
  return display_tile;
}

DisplayTile MapTranslator::create_display_tile_from_symbol_and_colour(const uchar symbol, const Colour colour)
{
  DisplayTile display_tile;
  
  display_tile.set_symbol(symbol);
  display_tile.set_colour(colour);
  
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
