#include "CoordUtils.hpp"
#include "CreatureFactory.hpp"
#include "SettlementGeneratorUtils.hpp"
#include "FeatureGenerator.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "GardenGeneratorFactory.hpp"
#include "ItemManager.hpp"
#include "MapUtils.hpp"
#include "RNG.hpp"
#include "ShopGenerator.hpp"
#include "TileGenerator.hpp"

using namespace std;

const int SettlementGeneratorUtils::PCT_CHANCE_BUILDING_SHOP = 5;

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

    if (type == TileType::TILE_TYPE_ROAD || type == TileType::TILE_TYPE_ROCK || type == TileType::TILE_TYPE_DUNGEON || type == TileType::TILE_TYPE_RIVER || type == TileType::TILE_TYPE_SPRINGS || type == TileType::TILE_TYPE_DOWN_STAIRCASE || type == TileType::TILE_TYPE_UP_STAIRCASE)
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
bool SettlementGeneratorUtils::generate_building_if_possible(MapPtr map, const BuildingGenerationParameters& bgp, vector<Building>& buildings, const int growth_rate, const bool allow_shop)
{
  bool generated = false;
  TileGenerator tg;
  
  int start_row = bgp.get_start_row();
  int end_row = bgp.get_end_row();
  int start_col = bgp.get_start_col();
  int end_col = bgp.get_end_col();
  TileType wall = bgp.get_wall_tile_type();
  CardinalDirection door_direction = bgp.get_door_direction();
  bool shop = false;

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
            current_tile = tg.generate(wall);
          }
          else
          {
            current_tile = tg.generate(TileType::TILE_TYPE_DUNGEON);
          }

          map->insert(cur_row, cur_col, current_tile);
        }
      }
    }

    if (growth_rate == 100)
    {
      if (allow_shop && RNG::percent_chance(PCT_CHANCE_BUILDING_SHOP))
      {
        // Set a flag to generate a shop after the building is otherwise done.
        shop = true;
      }
      else
      {
        generate_building_features(map, bgp);
        generate_building_creatures(map, bgp);
        generate_building_objects(map, bgp);
      }
    }

    // Create door
    pair<int, int> door_location = SettlementGeneratorUtils::get_door_location(start_row, end_row, start_col, end_col, door_direction);
    TilePtr door_tile = tg.generate(TileType::TILE_TYPE_DUNGEON);

    FeaturePtr door = FeatureGenerator::generate_door();
    door_tile->set_feature(door);

    // Track the building for later use - once all the buildings are generated
    // in a settlement, some might be used for shops or other purposes.
    Building building({ { start_row, start_col },{ end_row, end_col }, door_location });
    buildings.push_back(building);

    if (shop)
    {
      ShopGenerator sg;
      sg.generate_shop(map, building);
    }

    map->insert(door_location.first, door_location.second, door_tile);

    generated = true;
  }

  return generated;
}


void SettlementGeneratorUtils::generate_building_features(MapPtr map, const BuildingGenerationParameters& bgp)
{
  if (map != nullptr)
  {
    int start_row = bgp.get_start_row();
    int end_row = bgp.get_end_row();
    int start_col = bgp.get_start_col();
    int end_col = bgp.get_end_col();

    vector<ClassIdentifier> features = bgp.get_features();
    for (ClassIdentifier ci : features)
    {
      int rnd_y = RNG::range(start_row + 1, end_row - 1);
      int rnd_x = RNG::range(start_col + 1, end_col - 1);

      TilePtr tile = map->at(rnd_y, rnd_x);

      if (tile != nullptr)
      {
        FeaturePtr feature = FeatureGenerator::create_feature(ci);

        if (feature != nullptr && !tile->has_feature())
        {
          tile->set_feature(feature);
        }
      }
    }
  }
}

void SettlementGeneratorUtils::generate_building_creatures(MapPtr map, const BuildingGenerationParameters& bgp)
{
  if (map != nullptr)
  {
    Game& game = Game::instance();
    ActionManager& am = game.get_action_manager_ref();

    int start_row = bgp.get_start_row();
    int end_row = bgp.get_end_row();
    int start_col = bgp.get_start_col();
    int end_col = bgp.get_end_col();

    vector<string> creature_ids = bgp.get_creature_ids();

    if (!creature_ids.empty())
    {
      vector<Coordinate> coords = CoordUtils::get_coordinates_in_range({start_row+1, start_col+1}, {end_row-1, end_col-1});

      if (!coords.empty())
      {
        std::shuffle(coords.begin(), coords.end(), RNG::get_engine());

        while (!coords.empty() && !creature_ids.empty())
        {
          Coordinate c = coords.at(coords.size() - 1);

          // Is this tile available for the creature?  If so, generate the
          // creature and pop the creature ID.  Otherwise, pop the coordinate
          // and consider the next one.
          if (MapUtils::is_tile_available_for_creature(nullptr, map->at(c)))
          {
            string creature_id = creature_ids.at(creature_ids.size() - 1);
            CreatureFactory cf;
            CreaturePtr creature = cf.create_by_creature_id(am, creature_id, map);
            GameUtils::add_new_creature_to_map(game, creature, map, c);

            creature_ids.pop_back();
          }

          coords.pop_back();
        }
      }
    }
  }
}

void SettlementGeneratorUtils::generate_building_objects(MapPtr map, const BuildingGenerationParameters& bgp)
{
  if (map != nullptr)
  {
    int start_row = bgp.get_start_row();
    int end_row = bgp.get_end_row();
    int start_col = bgp.get_start_col();
    int end_col = bgp.get_end_col();

    vector<string> item_ids = bgp.get_item_ids();

    for (const string& item_id : item_ids)
    {
      int rnd_y = RNG::range(start_row + 1, end_row - 1);
      int rnd_x = RNG::range(start_col + 1, end_col - 1);

      TilePtr tile = map->at(rnd_y, rnd_x);

      if (tile != nullptr)
      {
        ItemPtr item = ItemManager::create_item(item_id);

        if (item != nullptr)
        {
          tile->get_items()->merge_or_add(item, InventoryAdditionType::INVENTORY_ADDITION_BACK);
        }
      }
    }
  }
}

pair<bool, int> SettlementGeneratorUtils::generate_sector_feature_if_possible(MapPtr map, const Coordinate& start, const Coordinate& end, const vector<shared_ptr<SectorFeature>>& sfeatures)
{
  pair<bool, int> placed = { false, -1 };

  if (!sfeatures.empty())
  {
    int idx = RNG::range(0, sfeatures.size() - 1);
    shared_ptr<SectorFeature> sf = sfeatures.at(idx);

    if (sf != nullptr)
    {
      placed.first = sf->generate(map, start, end);
      placed.second = idx;
    }
  }
  return placed;
}
