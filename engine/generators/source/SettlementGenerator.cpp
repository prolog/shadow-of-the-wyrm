#include "SettlementGenerator.hpp"
#include "TileGenerator.hpp"
#include "RNG.hpp"

using namespace std;

SettlementGenerator::SettlementGenerator() :
  GROWTH_RATE(100)
, PROBABILITY_DECREMENT(30)
, BUILDING_PROBABILITY(80)
, MIN_BLOCK_SIZE(3)
, BLOCK_SIZE(6)
, NS_DIVISOR(2)
, EW_DIVISOR(3)
{
}

SettlementGenerator::SettlementGenerator(const int growth_rate)
:GROWTH_RATE(growth_rate)
, PROBABILITY_DECREMENT(30)
, BUILDING_PROBABILITY(80)
, MIN_BLOCK_SIZE(3)
, BLOCK_SIZE(6)
, NS_DIVISOR(2)
, EW_DIVISOR(3)
{
}

MapPtr SettlementGenerator::generate(MapPtr map)
{
  MapPtr result_map = MapPtr(new Map(*map));

  result_map = generate_roads_and_buildings(result_map);
  result_map = populate_settlement(result_map);

  return result_map;
}

MapPtr SettlementGenerator::generate_roads_and_buildings(MapPtr map)
{
  MapPtr result_map = MapPtr(new Map(*map));

  int settlement_type = RNG::range(1, 2);

  switch(settlement_type)
  {
    case 1:
    case 2:
      result_map = generate_settlement_with_square_and_cardinal_roads(result_map);
      break;
    default:
      break;
  }

  return result_map;
}

MapPtr SettlementGenerator::generate_square(MapPtr map, const int start_row, const int start_col, const int square_size)
{
  MapPtr result_map = MapPtr(new Map(*map));

  int road_top    = start_row - 1;
  int road_bottom = start_row+square_size+1;
  int road_left   = start_col-1;
  int road_right  = start_col+square_size+1;

  for (int current_row = road_top; current_row <= road_bottom; current_row++)
  {
    for (int current_col = road_left; current_col <= road_right; current_col++)
    {
      int rand = RNG::range(1, 100);

      if (rand <= GROWTH_RATE)
      {
        if ((current_row == road_top) || (current_row == road_bottom) || (current_col == road_left) || (current_col == road_right))
        {
          TilePtr road_tile = TileGenerator::generate(TILE_TYPE_ROAD);
          result_map->insert(current_row, current_col, road_tile);
        }
        else
        {
          TilePtr square_tile;

          if ((current_col + current_row) % 2 == 0)
          {
            square_tile = TileGenerator::generate(TILE_TYPE_FIELD);
          }
          else
          {
            square_tile = TileGenerator::generate(TILE_TYPE_TREE);
          }

          result_map->insert(current_row, current_col, square_tile);
        }
      }
    }
  }

  return result_map;
}

bool SettlementGenerator::does_building_overlap(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  bool building_will_overlap = false;

  for (int cur_row = start_row; cur_row <= end_row; cur_row++)
  {
    for (int cur_col = start_col; cur_col <= end_col; cur_col++)
    {
      if (does_tile_overlap(map, cur_row, cur_col))
      {
        cout << "Tile overlaps.  Tile underneath: " << map->at(cur_row, cur_col)->get_tile_type() << " r/c:" << cur_row << "," << cur_col << endl;
        building_will_overlap = true;
        break;
      }
    }
  }

  return building_will_overlap;
}

// JCD FIXME: Move to Generator someday.
bool SettlementGenerator::does_tile_overlap(MapPtr map, const int row, const int col)
{
  bool tile_overlaps = false;

  Dimensions d = map->size();
  int max_rows = d.get_y();
  int max_cols = d.get_x();

  if (row < max_rows && col < max_cols)
  {
    TilePtr tile  = map->at(row, col);
    TileType type = tile->get_tile_type();

    if (type == TILE_TYPE_ROAD || type == TILE_TYPE_ROCK || type == TILE_TYPE_DUNGEON)
    {
      tile_overlaps = true;
    }

    return tile_overlaps;
  }

  return true; // Don't lay a tile over a non-existant space!
}

pair<int, int> SettlementGenerator::get_door_location(const int start_row, const int end_row, const int start_col, const int end_col, const CardinalDirection door_direction)
{
  pair<int, int> result = make_pair(start_row, end_col); // This default should never be used.

  switch(door_direction)
  {
    case CARDINAL_DIRECTION_NORTH:
      result = make_pair(start_row, (start_col + end_col) / 2);
      break;
    case CARDINAL_DIRECTION_SOUTH:
      result = make_pair(end_row, (start_col + end_col) / 2);
      break;
    case CARDINAL_DIRECTION_EAST:
      result = make_pair((start_row + end_row) / 2, end_col);
      break;
    case CARDINAL_DIRECTION_WEST:
      result = make_pair((start_row + end_row) / 2, start_col);
    default:
      break;
  }

  return result;
}

MapPtr SettlementGenerator::generate_building_if_possible(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col, const CardinalDirection door_direction)
{
  Dimensions d = map->size();
  int max_row = d.get_y();
  int max_col = d.get_x();

  if (start_row < 0 || end_row >= max_row || start_col < 0 || end_col >= max_col)
  {
    return map;
  }

  if (does_building_overlap(map, start_row, end_row, start_col, end_col))
  {
    cout << "Building overlaps." << endl;
    return map;
  }
  else
  {
    MapPtr result_map = MapPtr(new Map(*map));

    // Draw building
    int rand;
    TilePtr current_tile;
    for (int cur_row = start_row; cur_row <= end_row; cur_row++)
    {
      for (int cur_col = start_col; cur_col <= end_col; cur_col++)
      {
        rand = RNG::range(1, 100);

        if (rand <= GROWTH_RATE)
        {
          if (cur_row == start_row || cur_row == end_row || cur_col == start_col || cur_col == end_col)
          {
            current_tile = TileGenerator::generate(TILE_TYPE_ROCK);
          }
          else
          {
            current_tile = TileGenerator::generate(TILE_TYPE_DUNGEON);
          }

          result_map->insert(cur_row, cur_col, current_tile);
        }
      }
    }

    // Create door
    pair<int, int> door_location = get_door_location(start_row, end_row, start_col, end_col, door_direction);
    TilePtr door_tile = TileGenerator::generate(TILE_TYPE_DUNGEON);
    result_map->insert(door_location.first, door_location.second, door_tile);

    return result_map;
  }
}

// JCD FIXME: The overlap seems off.
MapPtr SettlementGenerator::generate_road_north(MapPtr map, const int start_row, const int start_col, const int road_length, const int probability, const int block_modifier)
{
  MapPtr result_map = MapPtr(new Map(*map));

  int rand = RNG::range(1, 100);
  int counter = 0;
  int current_length = 1;
  int current_row = start_row;

  if (rand <= probability)
  {
    while (current_length <= road_length)
    {
      rand = RNG::range(1, 100);

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
            cout << "Current row: " << current_row << ", end row: " << (current_row + building_size) << endl;
            result_map = generate_building_if_possible(result_map, current_row, current_row+building_size, start_col-building_size-2, start_col-2, CARDINAL_DIRECTION_EAST);
          }
        }
        else
        {
          int west_length = RNG::range(start_col/2, start_col-2);
          result_map = generate_road_west(result_map, current_row + (counter/2), start_col, west_length, probability-PROBABILITY_DECREMENT, block_modifier+1);
        }

        // East side
        building_or_road = RNG::range(1, 100);

        if (building_or_road < BUILDING_PROBABILITY)
        {
           // Building on east side
          building_size = RNG::range(BLOCK_SIZE-2, BLOCK_SIZE) - block_modifier;

          if (building_size >= MIN_BLOCK_SIZE)
          {
            cout << "Current row: " << current_row << ", end row: " << (current_row + building_size) << endl;
            result_map = generate_building_if_possible(result_map, current_row, current_row+building_size, start_col+2, start_col+building_size+2, CARDINAL_DIRECTION_WEST);
          }
        }
        else
        {
          int east_length = RNG::range(start_col/2, start_col-2);
          result_map = generate_road_east(result_map, current_row + (counter/2), start_col, east_length, probability-PROBABILITY_DECREMENT, block_modifier+1);
        }

        counter = 0;
      }

      if (rand <= GROWTH_RATE)
      {
        if (!does_tile_overlap(map, current_row, start_col) || (probability == 100))
        {
          TilePtr road_tile = TileGenerator::generate(TILE_TYPE_ROAD);
          result_map->insert(current_row, start_col, road_tile);
        }
        else
        {
          // We've gone too far.
          return result_map;
        }
      }

      current_row--;
      current_length++;
      counter++;
    }
  }

  return result_map;
}

MapPtr SettlementGenerator::generate_road_south(MapPtr map, const int start_row, const int start_col, const int road_length, const int probability, const int block_modifier)
{
  Dimensions d = map->size();
  int max_rows = d.get_y();
  MapPtr result_map = MapPtr(new Map(*map));

  int rand = RNG::range(1, 100);
  int counter = BLOCK_SIZE;
  int current_length = 1;
  int current_row = start_row;

  if (rand <= probability)
  {
    while ((current_length <= road_length) && (current_row < max_rows))
    {
      rand = RNG::range(1, 100);
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
            result_map = generate_building_if_possible(result_map, start_row, start_row+building_size, start_col-building_size-2, start_col-2, CARDINAL_DIRECTION_EAST);
          }
        }
        else
        {
          int west_length = RNG::range(start_col/2, start_col-2);
          result_map = generate_road_west(result_map, current_row + (counter/2), start_col, west_length, probability-PROBABILITY_DECREMENT, block_modifier+1);
        }

        // East side
        building_or_road = RNG::range(1, 100);

        if (building_or_road < BUILDING_PROBABILITY)
        {
           // Building on east side
          building_size = RNG::range(BLOCK_SIZE-2, BLOCK_SIZE) - block_modifier;

          if (building_size >= MIN_BLOCK_SIZE)
          {
            result_map = generate_building_if_possible(result_map, start_row, start_row+building_size, start_col+2, start_col+building_size+2, CARDINAL_DIRECTION_WEST);
          }
        }
        else
        {
          int east_length = RNG::range(start_col/2, start_col-2);
          result_map = generate_road_east(result_map, current_row + (counter/2), start_col, east_length, probability - PROBABILITY_DECREMENT, block_modifier+1);
        }
      }

      if (rand <= GROWTH_RATE)
      {
        if (!does_tile_overlap(result_map, current_row, start_col) || (probability == 100))
        {
          TilePtr road_tile = TileGenerator::generate(TILE_TYPE_ROAD);
          result_map->insert(current_row, start_col, road_tile);
        }
        else
        {
          // Too far!
          return result_map;
        }
      }

      if (counter == 0) counter = BLOCK_SIZE;

      current_row++;
      current_length++;
      counter--;
    }
  }

  return result_map;
}

MapPtr SettlementGenerator::generate_road_east(MapPtr map, const int start_row, const int start_col, const int road_length, const int probability, const int block_modifier)
{
  MapPtr result_map = MapPtr(new Map(*map));
  Dimensions d = result_map->size();

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
            result_map = generate_building_if_possible(result_map, start_row-building_size-1, start_row-1, current_col, current_col+building_size, CARDINAL_DIRECTION_SOUTH);
          }
        }
        else
        {
          int north_length = RNG::range(start_row/2, start_row-2);
          result_map = generate_road_north(result_map, start_row-1, current_col + (counter/2), north_length, probability-PROBABILITY_DECREMENT, block_modifier+1);
        }

        // South
        building_or_road = RNG::range(1, 100);

        if (building_or_road < BUILDING_PROBABILITY)
        {
           // Building on south side
          building_size = RNG::range(BLOCK_SIZE-2, BLOCK_SIZE) - block_modifier;

          if (building_size >= MIN_BLOCK_SIZE)
          {
            result_map = generate_building_if_possible(result_map, start_row+1, start_row+building_size+1, current_col, current_col+building_size, CARDINAL_DIRECTION_NORTH);
          }
        }
        else
        {
          int south_length = RNG::range((max_rows - start_row)/2, (max_rows - start_row)-2);
          result_map = generate_road_south(result_map, start_row+1, current_col + (counter / 2), south_length, probability - PROBABILITY_DECREMENT, block_modifier+1);
        }

        counter = 0;
      }

      if (rand <= GROWTH_RATE)
      {
        if (!does_tile_overlap(result_map, start_row, current_col) || (probability == 100))
        {
          TilePtr road_tile = TileGenerator::generate(TILE_TYPE_ROAD);
          result_map->insert(start_row, current_col, road_tile);
        }
        else
        {
          // Too far.
          return result_map;
        }
      }

      current_col++;
      current_length++;
      counter++;
    }
  }

  return result_map;
}

MapPtr SettlementGenerator::generate_road_west(MapPtr map, const int start_row, const int start_col, const int road_length, const int probability, const int block_modifier)
{
  MapPtr result_map = MapPtr(new Map(*map));
  Dimensions d = result_map->size();

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
            result_map = generate_building_if_possible(result_map, start_row-building_size-1, start_row-1, current_col, current_col+building_size, CARDINAL_DIRECTION_SOUTH);
          }
        }
        else
        {
          int north_length = RNG::range(start_row/2, start_row-2);
          result_map = generate_road_north(result_map, start_row-1, current_col + (counter/2), north_length, probability-PROBABILITY_DECREMENT, block_modifier+1);
        }

        // South
        building_or_road = RNG::range(1, 100);

        if (building_or_road < BUILDING_PROBABILITY)
        {
           // Building on south side
          building_size = RNG::range(BLOCK_SIZE-2, BLOCK_SIZE) - block_modifier;

          if (building_size >= MIN_BLOCK_SIZE)
          {
            result_map = generate_building_if_possible(result_map, start_row+1, start_row+building_size+1, current_col, current_col+building_size, CARDINAL_DIRECTION_NORTH);
          }
        }
        else
        {
          int south_length = RNG::range((max_rows - start_row)/2, (max_rows - start_row)-2);
          result_map = generate_road_south(result_map, start_row+1, current_col + (counter / 2), south_length, probability - PROBABILITY_DECREMENT, block_modifier+1);
        }

        counter = 0;
      }

      if (rand <= GROWTH_RATE)
      {
        if (!does_tile_overlap(result_map, start_row, current_col) || (probability == 100))
        {
          TilePtr road_tile = TileGenerator::generate(TILE_TYPE_ROAD);
          result_map->insert(start_row, current_col, road_tile);
        }
        else
        {
          // Too far.
          return result_map;
        }
      }

      current_col--;
      current_length++;
      counter++;
    }
  }

  return result_map;
}

MapPtr SettlementGenerator::generate_settlement_with_square_and_cardinal_roads(MapPtr map)
{
  MapPtr result_map = MapPtr(new Map(*map));
  Dimensions dim    = result_map->size();
  int num_rows      = dim.get_y();
  int num_cols      = dim.get_x();

  // Generate the central square.
  int square_size = RNG::range(2, 4);
  int start_row   = (num_rows / 2) - (square_size / 2);
  int start_col   = (num_cols / 2) - (square_size / 2);

  result_map = generate_square(result_map, start_row, start_col, square_size);

  // Generate the roads leading out, filling them with buildings.
  // JCD FIXME: Refactor, seriously.  This is ugly.
  result_map = generate_road_north(result_map, start_row-2, (start_col+(square_size/2)), start_row-2, 100);
  result_map = generate_road_south(result_map, (start_row+square_size+2), (start_col+(square_size/2)), num_rows-start_row+square_size+2, 100);
  result_map = generate_road_east(result_map, (start_row+(square_size/2)), (start_col+square_size+2), num_cols-start_col+square_size+2, 100);
  result_map = generate_road_west(result_map, (start_row+(square_size/2)), (start_col-2), start_col-2, 100);

  return result_map;
}

MapPtr SettlementGenerator::generate_settlement_with_winding_road(MapPtr map)
{
  return map;
}

MapPtr SettlementGenerator::populate_settlement(MapPtr map)
{
  MapPtr result_map = MapPtr(new Map(*map));

  return result_map;
}
