#include "SettlementGeneratorUtils.hpp"
#include "FeatureGenerator.hpp"
#include "GardenGeneratorFactory.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using namespace std;

// Building generation routines
pair<int, int> SettlementGeneratorUtils::get_door_location(const int start_row, const int end_row, const int start_col, const int end_col, const CardinalDirection door_direction)
{
  pair<int, int> result = make_pair(start_row, end_col); // This default should never be used.

  switch (door_direction)
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

// Routines to check to see whether a proposed building overlaps an existing generated building
// or road.
bool SettlementGeneratorUtils::does_building_overlap(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col, const int offset_extra)
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

bool SettlementGeneratorUtils::does_tile_overlap(MapPtr map, const int row, const int col)
{
  bool tile_overlaps = false;

  Dimensions d = map->size();
  int max_rows = d.get_y();
  int max_cols = d.get_x();

  if (row < max_rows && col < max_cols)
  {
    TilePtr tile = map->at(row, col);
    TileType type = tile->get_tile_type();

    if (type == TileType::TILE_TYPE_ROAD || type == TileType::TILE_TYPE_ROCK || type == TileType::TILE_TYPE_DUNGEON)
    {
      tile_overlaps = true;
    }

    return tile_overlaps;
  }

  return true; // Don't lay a tile over a non-existant space!
}

// Check to see if the given range of coordinates fall within the map's dimensions.
bool SettlementGeneratorUtils::is_rows_and_cols_in_range(const Dimensions& dim, const int start_row, const int end_row, const int start_col, const int end_col)
{
  if (start_row < 0 || end_row >= dim.get_y() || start_col < 0 || end_col >= dim.get_x())
  {
    return false;
  }

  return true;
}

// Generate a particular type of garden if possible, returning true if the garden
// could be generated, and false otherwise.
bool SettlementGeneratorUtils::generate_garden_if_possible(MapPtr map, const GardenType garden_type, const int start_row, const int end_row, const int start_col, const int end_col)
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
      SectorFeaturePtr garden_gen = GardenGeneratorFactory::create_garden_generator(garden_type);
      garden_gen->generate(map, make_pair(start_row, start_col), make_pair(end_row, end_col));
      generated = true;
    }
  }

  return generated;
}

// Generate a building if possible, returning true if a building could be generated,
// and false otherwise.
bool SettlementGeneratorUtils::generate_building_if_possible(MapPtr map, const BuildingGenerationParameters& bgp, vector<Building>& buildings, const int growth_rate)
{
  bool generated = false;
  TileGenerator tg;

  int start_row = bgp.get_start_row();
  int end_row = bgp.get_end_row();
  int start_col = bgp.get_start_col();
  int end_col = bgp.get_end_col();
  CardinalDirection door_direction = bgp.get_door_direction();

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
    pair<int, int> door_location = SettlementGeneratorUtils::get_door_location(start_row, end_row, start_col, end_col, door_direction);
    TilePtr door_tile = tg.generate(TileType::TILE_TYPE_DUNGEON);

    FeaturePtr door = FeatureGenerator::generate_door();
    door_tile->set_feature(door);

    // Track the building for later use - once all the buildings are generated
    // in a settlement, some might be used for shops or other purposes.
    buildings.push_back({ { start_row, start_col },{ end_row, end_col }, door_location });

    map->insert(door_location.first, door_location.second, door_tile);

    generated = true;
  }

  return generated;
}

