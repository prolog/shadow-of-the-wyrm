#include "SpiralDungeonGenerator.hpp"
#include "TileGenerator.hpp"
#include "RNG.hpp"

using namespace std;

SpiralDungeonGenerator::SpiralDungeonGenerator(const std::string& new_map_exit_id)
: DungeonGenerator(new_map_exit_id)
, SPACE_BETWEEN_SPIRALS(2)
{
}

// Place the staircase
MapPtr SpiralDungeonGenerator::place_random_staircase(MapPtr map, StaircaseTilePtr staircase_tile)
{
  Dimensions d = map->size();
  int max_row = d.get_y();
  int max_col = d.get_x();
  bool found = false;

  int rand_row;
  int rand_col;

  while (!found)
  {
    rand_row = RNG::range(0, max_row-1);
    rand_col = RNG::range(0, max_col-1);

    TilePtr random_tile  = map->at(rand_row, rand_col);
    TileType random_tile_type = random_tile->get_tile_type();

    if (random_tile_type == TileType::TILE_TYPE_DUNGEON)
    {
      map->insert(rand_row, rand_col, staircase_tile);
      found = true;
    }
  }

  return map;
}

// Place the staircases at random on the generated map.
MapPtr SpiralDungeonGenerator::place_staircases(MapPtr map, const bool place_up_stairs, const bool place_down_stairs)
{
  MapPtr result_map = map;

  if (place_up_stairs)
  {
    StaircaseTilePtr up_staircase = tg.generate_staircase(StaircaseType::STAIRCASE_UP);
    result_map = place_random_staircase(map, up_staircase);
  }

  if (place_down_stairs)
  {
    StaircaseTilePtr down_staircase = tg.generate_staircase(StaircaseType::STAIRCASE_DOWN);
    result_map = place_random_staircase(result_map, down_staircase);
  }

  return result_map;
}

// Recursively generate a spiral dungeon
void SpiralDungeonGenerator::generate_spiral(MapPtr map, const int current_row, const int current_col, const CardinalDirection direction, const int row_length, const int col_length)
{
  if (row_length < 0 || col_length < 0)
  {
    return;
  }
  else
  {
    // Check the current tile - if it's floor, we've come too far.
    TilePtr tile = map->at(current_row, current_col);
    if (tile->get_tile_type() == TileType::TILE_TYPE_DUNGEON)
    {
      return;
    }

    int new_row_length, new_col_length;
    int row_or_col_current;

    int current = 1;

    switch (direction)
    {
      // North goes to east.
      case CardinalDirection::CARDINAL_DIRECTION_NORTH:
        row_or_col_current = current_row;
        new_row_length = row_length - SPACE_BETWEEN_SPIRALS;
        while (current <= row_length)
        {
          tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
          map->insert(row_or_col_current, current_col, tile);
          row_or_col_current--;
          current++;
        }

        generate_spiral(map, row_or_col_current, current_col, CardinalDirection::CARDINAL_DIRECTION_EAST, new_row_length, col_length);
        break;
      // South goes to west.
      case CardinalDirection::CARDINAL_DIRECTION_SOUTH:
        row_or_col_current = current_row;
        new_row_length = row_length - SPACE_BETWEEN_SPIRALS;
        while (current <= row_length)
        {
          tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
          map->insert(row_or_col_current, current_col, tile);
          row_or_col_current++;
          current++;
        }

        generate_spiral(map, row_or_col_current, current_col, CardinalDirection::CARDINAL_DIRECTION_WEST, new_row_length, col_length);
        break;
      // East goes to south.
      case CardinalDirection::CARDINAL_DIRECTION_EAST:
        row_or_col_current = current_col;
        new_col_length = col_length - SPACE_BETWEEN_SPIRALS;
        while (current <= col_length)
        {
          tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
          map->insert(current_row, row_or_col_current, tile);
          row_or_col_current++;
          current++;
        }

        generate_spiral(map, current_row, row_or_col_current, CardinalDirection::CARDINAL_DIRECTION_SOUTH, row_length, new_col_length);
        break;
      // West goes to north.
      case CardinalDirection::CARDINAL_DIRECTION_WEST:
        row_or_col_current = current_col;
        new_col_length = col_length - SPACE_BETWEEN_SPIRALS;
        while (current <= col_length)
        {
          tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
          map->insert(current_row, row_or_col_current, tile);
          row_or_col_current--;
          current++;
        }

        generate_spiral(map, current_row, row_or_col_current, CardinalDirection::CARDINAL_DIRECTION_NORTH, row_length, new_col_length);
        break;
      default:
        return;
    }
  }
}

// Generate a spiral dungeon
MapPtr SpiralDungeonGenerator::generate_spiral_dungeon(MapPtr map)
{
  MapPtr result_map = std::make_shared<Map>(*map);
  Dimensions d = result_map->size();
  int max_row = d.get_y();
  int max_col = d.get_x();

  // Start in bottom right.
  int current_row = max_row - SPACE_BETWEEN_SPIRALS;
  int current_col = max_col - SPACE_BETWEEN_SPIRALS;
  int row_length  = current_row - SPACE_BETWEEN_SPIRALS;
  int col_length  = current_col - SPACE_BETWEEN_SPIRALS;

  generate_spiral(result_map, current_row, current_col, CardinalDirection::CARDINAL_DIRECTION_WEST, row_length, col_length);

  return result_map;
}

MapPtr SpiralDungeonGenerator::generate(const Dimensions& dimensions)
{
  MapPtr result_map = std::make_shared<Map>(dimensions);

  fill(result_map, TileType::TILE_TYPE_ROCK);
  result_map = generate_spiral_dungeon(result_map);
 // result_map = place_staircases(result_map);
 
  result_map->set_map_type(MapType::MAP_TYPE_UNDERWORLD);

  return result_map;
}
