#include <utility>
#include "BaseSettlementGenerator.hpp"
#include "FeatureGenerator.hpp"
#include "GardenGenerator.hpp"
#include "GardenGeneratorFactory.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using std::pair;
using std::make_pair;

BaseSettlementGenerator::BaseSettlementGenerator(MapPtr new_base_map)
: Generator(new_base_map->get_map_exit_id(), TileType::TILE_TYPE_VILLAGE),
base_map(new_base_map), growth_rate(100)
, PROBABILITY_DECREMENT(30)
, BUILDING_PROBABILITY(80)
, MIN_BLOCK_SIZE(3)
, BLOCK_SIZE(6)
, NS_DIVISOR(2)
, EW_DIVISOR(3)
{
}

BaseSettlementGenerator::BaseSettlementGenerator(MapPtr new_base_map, const int new_growth_rate)
: Generator(new_base_map->get_map_exit_id(), TileType::TILE_TYPE_VILLAGE),
base_map(new_base_map), growth_rate(new_growth_rate)
, PROBABILITY_DECREMENT(30)
, BUILDING_PROBABILITY(80)
, MIN_BLOCK_SIZE(3)
, BLOCK_SIZE(6)
, NS_DIVISOR(2)
, EW_DIVISOR(3)
{
}

// Once generated, settlements are permanent.
bool BaseSettlementGenerator::get_permanence_default() const
{
  return true;
}

bool BaseSettlementGenerator::get_ignore_creature_generation_level_checks() const
{
  return true;
}


// Routines to check to see whether a proposed building overlaps an existing generated building
// or road.
bool BaseSettlementGenerator::does_building_overlap(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col, const int offset_extra)
{
  bool building_will_overlap = false;

  for (int cur_row = start_row - offset_extra; cur_row <= end_row + offset_extra; cur_row++)
  {
    for (int cur_col = start_col - offset_extra; cur_col <= end_col + offset_extra; cur_col++)
    {
      if (does_tile_overlap(map, cur_row, cur_col))
      {
        building_will_overlap = true;
        break;
      }
    }
  }

  return building_will_overlap;
}

bool BaseSettlementGenerator::does_tile_overlap(MapPtr map, const int row, const int col)
{
  bool tile_overlaps = false;

  Dimensions d = map->size();
  int max_rows = d.get_y();
  int max_cols = d.get_x();

  if (row < max_rows && col < max_cols)
  {
    TilePtr tile  = map->at(row, col);
    TileType type = tile->get_tile_type();

    if (type == TileType::TILE_TYPE_ROAD || type == TileType::TILE_TYPE_ROCK || type == TileType::TILE_TYPE_DUNGEON)
    {
      tile_overlaps = true;
    }

    return tile_overlaps;
  }

  return true; // Don't lay a tile over a non-existant space!
}

// Building generation routines
pair<int, int> BaseSettlementGenerator::get_door_location(const int start_row, const int end_row, const int start_col, const int end_col, const CardinalDirection door_direction)
{
  pair<int, int> result = make_pair(start_row, end_col); // This default should never be used.

  switch(door_direction)
  {
    case CardinalDirection::CARDINAL_DIRECTION_NORTH:
      result = make_pair(start_row, (start_col + end_col) / 2);
      break;
    case CardinalDirection::CARDINAL_DIRECTION_SOUTH:
      result = make_pair(end_row, (start_col + end_col) / 2);
      break;
    case CardinalDirection::CARDINAL_DIRECTION_EAST:
      result = make_pair((start_row + end_row) / 2, end_col);
      break;
    case CardinalDirection::CARDINAL_DIRECTION_WEST:
      result = make_pair((start_row + end_row) / 2, start_col);
    default:
      break;
  }

  return result;
}

// Check to see if the given range of coordinates fall within the map's dimensions.
bool BaseSettlementGenerator::is_rows_and_cols_in_range(const Dimensions& dim, const int start_row, const int end_row, const int start_col, const int end_col)
{
  if (start_row < 0 || end_row >= dim.get_y() || start_col < 0 || end_col >= dim.get_x())
  {
    return false;
  }
  
  return true;
}

// Generate a particular type of garden if possible, returning true if the garden
// could be generated, and false otherwise.
bool BaseSettlementGenerator::generate_garden_if_possible(MapPtr map, const GardenType garden_type, const int start_row, const int end_row, const int start_col, const int end_col)
{
  bool generated = false;
  
  if (!is_rows_and_cols_in_range(map->size(), start_row, end_row, start_col, end_col))
  {
    return generated;
  }
  else
  {
    if (does_building_overlap(map, start_row, end_row, start_col, end_col))
    {
      return generated;
    }
    else
    {
      GardenGeneratorPtr garden_gen = GardenGeneratorFactory::create_garden_generator(garden_type, map, start_row, start_col, (end_row - start_row), (end_col - start_col));
      garden_gen->generate();
      generated = true;
    }
  }
  
  return generated;
}

// Generate a building if possible, returning true if a building could be generated,
// and false otherwise.
bool BaseSettlementGenerator::generate_building_if_possible(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col, const CardinalDirection door_direction)
{
  bool generated = false;
  TileGenerator tg;

  if (!is_rows_and_cols_in_range(map->size(), start_row, end_row, start_col, end_col))
  {
    return generated;
  }

  if (does_building_overlap(map, start_row, end_row, start_col, end_col))
  {
    return generated;
  }
  else
  {
    // Draw building
    int rand;
    TilePtr current_tile;
    for (int cur_row = start_row; cur_row <= end_row; cur_row++)
    {
      for (int cur_col = start_col; cur_col <= end_col; cur_col++)
      {
        rand = RNG::range(1, 100);

        if (rand <= growth_rate)
        {
          if (cur_row == start_row || cur_row == end_row || cur_col == start_col || cur_col == end_col)
          {
            current_tile = tg.generate(TileType::TILE_TYPE_ROCK);
          }
          else
          {
            current_tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
          }

          map->insert(cur_row, cur_col, current_tile);
        }
      }
    }

    // Create door
    pair<int, int> door_location = get_door_location(start_row, end_row, start_col, end_col, door_direction);
    TilePtr door_tile = tg.generate(TileType::TILE_TYPE_DUNGEON);

    FeaturePtr door = FeatureGenerator::generate_door();
    door_tile->set_feature(door);

    map->insert(door_location.first, door_location.second, door_tile);
    generated = true;
  }
  
  return generated;
}

void BaseSettlementGenerator::generate_road_north(MapPtr map, const int start_row, const int start_col, const int road_length, const int probability, const int block_modifier, bool recurse)
{
  int rand = RNG::range(1, 100);
  int counter = 0;
  int current_length = 1;
  int current_row = start_row;
  TileGenerator tg;

  if (rand <= probability)
  {
    while (current_length <= road_length)
    {
      rand = RNG::range(1, 100);

      if (recurse)
      {
        if (counter == (start_row / NS_DIVISOR))
        {
          // West side
          int building_or_road = RNG::range(1, 100);
          int building_size;

          if (building_or_road < BUILDING_PROBABILITY)
          {
            // Building on west side
            building_size = RNG::range(BLOCK_SIZE-2, BLOCK_SIZE) - block_modifier;

            if (building_size >= MIN_BLOCK_SIZE)
            {
              generate_building_if_possible(map, current_row, current_row + building_size, start_col - building_size - 2, start_col - 2, CardinalDirection::CARDINAL_DIRECTION_EAST);
            }
          }
          else
          {
            int west_length = RNG::range(start_col/2, start_col-2);
            generate_road_west(map, current_row + (counter/2), start_col, west_length, probability-PROBABILITY_DECREMENT, block_modifier+1);
          }

          // East side
          building_or_road = RNG::range(1, 100);

          if (building_or_road < BUILDING_PROBABILITY)
          {
             // Building on east side
            building_size = RNG::range(BLOCK_SIZE-2, BLOCK_SIZE) - block_modifier;

            if (building_size >= MIN_BLOCK_SIZE)
            {
              generate_building_if_possible(map, current_row, current_row + building_size, start_col + 2, start_col + building_size + 2, CardinalDirection::CARDINAL_DIRECTION_WEST);
            }
          }
          else
          {
            int east_length = RNG::range(start_col/2, start_col-2);
            generate_road_east(map, current_row + (counter/2), start_col, east_length, probability-PROBABILITY_DECREMENT, block_modifier+1);
          }

          counter = 0;
        }
      }

      if (rand <= growth_rate)
      {
        if (!does_tile_overlap(map, current_row, start_col) || (probability == 100))
        {
          TilePtr road_tile = tg.generate(TileType::TILE_TYPE_ROAD);
          map->insert(current_row, start_col, road_tile);
        }
        else
        {
          // We've gone too far.
          return;
        }
      }

      current_row--;
      current_length++;
      counter++;
    }
  }
}

void BaseSettlementGenerator::generate_road_south(MapPtr map, const int start_row, const int start_col, const int road_length, const int probability, const int block_modifier, bool recurse)
{
  TileGenerator tg;
  Dimensions d = map->size();
  int max_rows = d.get_y();

  int rand = RNG::range(1, 100);
  int counter = BLOCK_SIZE;
  int current_length = 1;
  int current_row = start_row;

  if (rand <= probability)
  {
    while ((current_length <= road_length) && (current_row < max_rows))
    {
      rand = RNG::range(1, 100);
      
      if (recurse)
      {
        if (counter == ((max_rows-start_row) / NS_DIVISOR))
        {
          // West side
          int building_or_road = RNG::range(1, 100);
          int building_size;

          if (building_or_road < BUILDING_PROBABILITY)
          {
            // Building on west side
            building_size = RNG::range(BLOCK_SIZE-2, BLOCK_SIZE-1) - block_modifier;

            if (building_size >= block_modifier)
            {
              generate_building_if_possible(map, start_row, start_row + building_size, start_col - building_size - 2, start_col - 2, CardinalDirection::CARDINAL_DIRECTION_EAST);
            }
          }
          else
          {
            int west_length = RNG::range(start_col/2, start_col-2);
            generate_road_west(map, current_row + (counter/2), start_col, west_length, probability-PROBABILITY_DECREMENT, block_modifier+1);
          }

          // East side
          building_or_road = RNG::range(1, 100);

          if (building_or_road < BUILDING_PROBABILITY)
          {
             // Building on east side
            building_size = RNG::range(BLOCK_SIZE-2, BLOCK_SIZE) - block_modifier;

            if (building_size >= MIN_BLOCK_SIZE)
            {
              generate_building_if_possible(map, start_row, start_row + building_size, start_col + 2, start_col + building_size + 2, CardinalDirection::CARDINAL_DIRECTION_WEST);
            }
          }
          else
          {
            int east_length = RNG::range(start_col/2, start_col-2);
            generate_road_east(map, current_row + (counter/2), start_col, east_length, probability - PROBABILITY_DECREMENT, block_modifier+1);
          }
        }
      }

      if (rand <= growth_rate)
      {
        if (!does_tile_overlap(map, current_row, start_col) || (probability == 100))
        {
          TilePtr road_tile = tg.generate(TileType::TILE_TYPE_ROAD);
          map->insert(current_row, start_col, road_tile);
        }
        else
        {
          // Too far!
          return;
        }
      }

      if (counter == 0) counter = BLOCK_SIZE;

      current_row++;
      current_length++;
      counter--;
    }
  }
}

void BaseSettlementGenerator::generate_road_east(MapPtr map, const int start_row, const int start_col, const int road_length, const int probability, const int block_modifier, bool recurse)
{
  Dimensions d = map->size();
  TileGenerator tg;

  int max_rows = d.get_y();
  int max_cols = d.get_x();
  int rand = RNG::range(1, 100);
  int counter = 1;
  int current_col = start_col;
  int current_length = 1;

  if (rand <= probability)
  {
    while((current_length <= road_length) && (current_col < max_cols))
    {
      rand = RNG::range(1, 100);
      
      if (recurse)
      {
        if (counter == ((max_cols - start_col) / EW_DIVISOR))
        {
          // North side
          int building_or_road = RNG::range(1, 100);
          int building_size;

          // JCD FIXME FIXME FIXME
          if (building_or_road < BUILDING_PROBABILITY)
          {
            // Building on north side
            building_size = RNG::range(BLOCK_SIZE-2, BLOCK_SIZE-1) - block_modifier;

            if (building_size >= MIN_BLOCK_SIZE)
            {
              generate_building_if_possible(map, start_row - building_size - 1, start_row - 1, current_col, current_col + building_size, CardinalDirection::CARDINAL_DIRECTION_SOUTH);
            }
          }
          else
          {
            int north_length = RNG::range(start_row/2, start_row-2);
            generate_road_north(map, start_row-1, current_col + (counter/2), north_length, probability-PROBABILITY_DECREMENT, block_modifier+1);
          }

          // South
          building_or_road = RNG::range(1, 100);

          if (building_or_road < BUILDING_PROBABILITY)
          {
             // Building on south side
            building_size = RNG::range(BLOCK_SIZE-2, BLOCK_SIZE) - block_modifier;

            if (building_size >= MIN_BLOCK_SIZE)
            {
              generate_building_if_possible(map, start_row + 1, start_row + building_size + 1, current_col, current_col + building_size, CardinalDirection::CARDINAL_DIRECTION_NORTH);
            }
          }
          else
          {
            int south_length = RNG::range((max_rows - start_row)/2, (max_rows - start_row)-2);
            generate_road_south(map, start_row+1, current_col + (counter / 2), south_length, probability - PROBABILITY_DECREMENT, block_modifier+1);
          }

          counter = 0;
        }
      }

      if (rand <= growth_rate)
      {
        if (!does_tile_overlap(map, start_row, current_col) || (probability == 100))
        {
          TilePtr road_tile = tg.generate(TileType::TILE_TYPE_ROAD);
          map->insert(start_row, current_col, road_tile);
        }
        else
        {
          // Too far.
          return;
        }
      }

      current_col++;
      current_length++;
      counter++;
    }
  }
}

void BaseSettlementGenerator::generate_road_west(MapPtr map, const int start_row, const int start_col, const int road_length, const int probability, const int block_modifier, bool recurse)
{
  TileGenerator tg;
  Dimensions d = map->size();

  int max_rows = d.get_y();
  int max_cols = d.get_x();
  int rand = RNG::range(1, 100);
  int counter = 1;
  int current_col = start_col;
  int current_length = 1;

  if (rand <= probability)
  {
    while(current_length <= road_length)
    {
      rand = RNG::range(1, 100);
      
      if (recurse)
      {        
        if (counter == ((max_cols - start_col) / EW_DIVISOR))
        {
          // North side
          int building_or_road = RNG::range(1, 100);
          int building_size;

          // JCD FIXME FIXME FIXME
          if (building_or_road < BUILDING_PROBABILITY)
          {
            // Building on north side
            building_size = RNG::range(BLOCK_SIZE-2, BLOCK_SIZE-1) - block_modifier;

            if (building_size >= MIN_BLOCK_SIZE)
            {
              generate_building_if_possible(map, start_row - building_size - 1, start_row - 1, current_col, current_col + building_size, CardinalDirection::CARDINAL_DIRECTION_SOUTH);
            }
          }
          else
          {
            int north_length = RNG::range(start_row/2, start_row-2);
            generate_road_north(map, start_row-1, current_col + (counter/2), north_length, probability-PROBABILITY_DECREMENT, block_modifier+1);
          }

          // South
          building_or_road = RNG::range(1, 100);

          if (building_or_road < BUILDING_PROBABILITY)
          {
             // Building on south side
            building_size = RNG::range(BLOCK_SIZE-2, BLOCK_SIZE) - block_modifier;

            if (building_size >= MIN_BLOCK_SIZE)
            {
              generate_building_if_possible(map, start_row + 1, start_row + building_size + 1, current_col, current_col + building_size, CardinalDirection::CARDINAL_DIRECTION_NORTH);
            }
          }
          else
          {
            int south_length = RNG::range((max_rows - start_row)/2, (max_rows - start_row)-2);
            generate_road_south(map, start_row+1, current_col + (counter / 2), south_length, probability - PROBABILITY_DECREMENT, block_modifier+1);
          }

          counter = 0;
        }
      }

      if (rand <= growth_rate)
      {
        if (!does_tile_overlap(map, start_row, current_col) || (probability == 100))
        {
          TilePtr road_tile = tg.generate(TileType::TILE_TYPE_ROAD);
          map->insert(start_row, current_col, road_tile);
        }
        else
        {
          // Too far.
          return;
        }
      }

      current_col--;
      current_length++;
      counter++;
    }
  }
}
