#include "FeatureGenerator.hpp"
#include "FieldGenerator.hpp"
#include "KeepGenerator.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using std::string;

KeepGenerator::KeepGenerator(const string& map_exit_id, const int chance_decay)
  : Generator(map_exit_id, TileType::TILE_TYPE_KEEP), PCT_CHANCE_DECAY(chance_decay)
{
  FieldGenerator fg(map_exit_id);
  Dimensions dim;

  base_map = fg.generate(dim);
}

KeepGenerator::KeepGenerator(MapPtr new_base_map, const int chance_decay)
: Generator(new_base_map->get_map_exit_id(), TileType::TILE_TYPE_KEEP)
, base_map(new_base_map)
, PCT_CHANCE_DECAY(chance_decay)
{
}

MapPtr KeepGenerator::generate(const Dimensions& /*dim*/)
{
  // Ignore the dimensions, since we have a base map already!
  return generate();
}

// Generate a square keep, centre it on the map.
MapPtr KeepGenerator::generate()
{
  MapPtr result_map = std::make_shared<Map>(*base_map);
  Dimensions dimensions = result_map->size();

  int max_height = dimensions.get_y();
  int max_width  = dimensions.get_x();

  int height = RNG::irange(0.5 * max_height, 0.8 * max_height);
  int width  = RNG::irange(0.5 * max_width, 0.8 * max_width);

  int start_row = (max_height - height) / 2;
  int start_col = (max_width - width) / 2;

  create_keep    (result_map, start_row, start_col, height, width);
  create_entrance(result_map, start_row, start_col, height, width);
  populate_keep (result_map, start_row, start_col, height, width);

  return result_map;
}

bool KeepGenerator::get_permanence_default() const
{
  return true;
}

void KeepGenerator::create_keep(MapPtr result_map, const int start_row, const int start_col, const int height, const int width)
{
  TilePtr tile;
  TileGenerator tg;

  // Create the keep
  for (int y = start_row; y <= start_row + height; y++)
  {
    for (int x = start_col; x <= start_col + width; x++)
    {
      int ruin_pct = RNG::range(1, 100);

      if (ruin_pct < PCT_CHANCE_DECAY)
      {
        // Do nothing - keep whatever tile was generated previously.  This is a quick and dirty way of representing
        // decay and ruin.
      }
      else
      {
        // If it's at a boundary, draw a wall.
        if (y == start_row || (y == (start_row+height)) || (x == start_col) || (x == (start_col+width)))
        {
          tile = tg.generate(TileType::TILE_TYPE_ROCK);
          result_map->insert(y, x, tile);
        }
        // Else, draw a floor.
        else
        {
          tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
          result_map->insert(y, x, tile);
        }
      }
    }
  }
}

// Add random features to the keep
void KeepGenerator::populate_keep(MapPtr result_map, const int start_row, const int start_col, const int height, const int width)
{
  TileGenerator tg;
  TilePtr tile;
  int wall_row = RNG::range((start_row+3), (start_row + height - 3));
  int num_rooms = RNG::range(3, 5);
  int counter_stop = ((width-2) / num_rooms);
  int door_hole = counter_stop / 2;
  int counter = 1;
  int dug_rooms = 0;

  for (int wall_col = start_col+1; wall_col < start_col + width; wall_col++)
  {
    if (counter == counter_stop && (dug_rooms < num_rooms-1))
    {
      // Draw the wall upwards.
      tile = tg.generate(TileType::TILE_TYPE_ROCK);

      for (int current_row = wall_row; current_row >= start_row; current_row--)
      {
        result_map->insert(current_row, wall_col, tile);
      }

      dug_rooms++;
      counter = 0;

      // Potentially dig a wall downward.
      int rand = RNG::range(1, 100);
      if (rand < 50)
      {
        int door_row = (wall_row + (start_row+height))/2;
        for (int new_row = wall_row; new_row < start_row + height; new_row++)
        {
          if (new_row == door_row)
          {
            tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
          }
          else
          {
            tile = tg.generate(TileType::TILE_TYPE_ROCK);
          }

          result_map->insert(new_row, wall_col, tile);
        }
      }
    }
    else if (counter == door_hole)
    {
      tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
      
      if (PCT_CHANCE_DECAY == 0)
      {
        FeaturePtr door = FeatureGenerator::generate_door();
        tile->set_feature(door);
      }
    }
    else
    {
      tile = tg.generate(TileType::TILE_TYPE_ROCK);
    }

    result_map->insert(wall_row, wall_col, tile);

    counter++;
  }
}

// Dig the door
void KeepGenerator::create_entrance(MapPtr result_map, const int start_row, const int start_col, const int height, const int width)
{
  TileGenerator tg;
  TilePtr tile;

  for (int col = (start_col+width/2)-1; col < (start_col+width/2)+2; col++)
  {
    tile = tg.generate(TileType::TILE_TYPE_DUNGEON);      
    
    if (PCT_CHANCE_DECAY == 0) // If we haven't begun to decay, add the door
    {
      FeaturePtr door = FeatureGenerator::generate_door();
      tile->set_feature(door);
    }
    
    result_map->insert(start_row+height, col, tile);
  }
}

