#include <utility>
#include "BaseSettlementGenerator.hpp"
#include "BuildingConfigFactory.hpp"
#include "CreatureGenerationManager.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "GraveyardSectorFeature.hpp"
#include "LibrarySectorFeature.hpp"
#include "ParkSectorFeature.hpp"
#include "RNG.hpp"
#include "SettlementGeneratorUtils.hpp"
#include "ShrineSectorFeature.hpp"
#include "TavernSectorFeature.hpp"
#include "TileGenerator.hpp"
#include "FruitVegetableGardenGenerator.hpp"

using namespace std;

BaseSettlementGenerator::BaseSettlementGenerator(MapPtr new_base_map)
: Generator(new_base_map->get_map_exit_id(), TileType::TILE_TYPE_VILLAGE),
base_map(new_base_map), growth_rate(100), pct_chance_sector_feature(20)
, PROBABILITY_DECREMENT(30)
, WORKSHOP_PROBABILITY(20)
, BUILDING_PROBABILITY(80)
, MIN_BLOCK_SIZE(3)
, BLOCK_SIZE(6)
, NS_DIVISOR(2)
, EW_DIVISOR(3)
, WELLS_MIN(0)
, WELLS_MAX(3)
, HIRELING_PROBABILITY(70)
{
}

BaseSettlementGenerator::BaseSettlementGenerator(MapPtr new_base_map, const int new_growth_rate)
: Generator(new_base_map->get_map_exit_id(), TileType::TILE_TYPE_VILLAGE),
base_map(new_base_map), growth_rate(new_growth_rate), pct_chance_sector_feature(20)
, PROBABILITY_DECREMENT(30)
, WORKSHOP_PROBABILITY(20)
, BUILDING_PROBABILITY(80)
, MIN_BLOCK_SIZE(3)
, BLOCK_SIZE(6)
, NS_DIVISOR(2)
, EW_DIVISOR(3)
, WELLS_MIN(0)
, WELLS_MAX(3)
, HIRELING_PROBABILITY(70)
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


void BaseSettlementGenerator::generate_road_north(MapPtr map, const int start_row, const int start_col, const int road_length, const int probability, const int block_modifier, bool recurse)
{
  int rand = RNG::range(1, 100);
  int counter = 0;
  int current_length = 1;
  int current_row = start_row;
  TileGenerator tg;
  BuildingConfigFactory bcf;
  
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
              vector<ClassIdentifier> cl_ids = bcf.create_house_or_workshop_features(WORKSHOP_PROBABILITY);
              BuildingGenerationParameters bgp(current_row, current_row + building_size, start_col - building_size - 2, start_col - 2, CardinalDirection::CARDINAL_DIRECTION_EAST, false, cl_ids, bcf.create_creature_ids(cl_ids), bcf.create_item_ids(cl_ids));
              SettlementGeneratorUtils::generate_building_if_possible(map, bgp, buildings, growth_rate);
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
              vector<ClassIdentifier> cl_ids = bcf.create_house_or_workshop_features(WORKSHOP_PROBABILITY);
              BuildingGenerationParameters bgp(current_row, current_row + building_size, start_col + 2, start_col + building_size + 2, CardinalDirection::CARDINAL_DIRECTION_WEST, false, cl_ids, bcf.create_creature_ids(cl_ids), bcf.create_item_ids(cl_ids));
              SettlementGeneratorUtils::generate_building_if_possible(map, bgp, buildings, growth_rate);
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
        if (!SettlementGeneratorUtils::does_tile_overlap(map, current_row, start_col) || (probability == 100))
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
  BuildingConfigFactory bcf;

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
              vector<ClassIdentifier> cl_ids = bcf.create_house_or_workshop_features(WORKSHOP_PROBABILITY);
              BuildingGenerationParameters bgp(start_row, start_row + building_size, start_col - building_size - 2, start_col - 2, CardinalDirection::CARDINAL_DIRECTION_EAST, false, cl_ids, bcf.create_creature_ids(cl_ids), bcf.create_item_ids(cl_ids));
              SettlementGeneratorUtils::generate_building_if_possible(map, bgp, buildings, growth_rate);
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
              vector<ClassIdentifier> cl_ids = bcf.create_house_or_workshop_features(WORKSHOP_PROBABILITY);
              BuildingGenerationParameters bgp(start_row, start_row + building_size, start_col + 2, start_col + building_size + 2, CardinalDirection::CARDINAL_DIRECTION_WEST, false, cl_ids, bcf.create_creature_ids(cl_ids), bcf.create_item_ids(cl_ids));
              SettlementGeneratorUtils::generate_building_if_possible(map, bgp, buildings, growth_rate);
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
        if (!SettlementGeneratorUtils::does_tile_overlap(map, current_row, start_col) || (probability == 100))
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
  BuildingConfigFactory bcf;

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
              vector<ClassIdentifier> cl_ids = bcf.create_house_or_workshop_features(WORKSHOP_PROBABILITY);
              BuildingGenerationParameters bgp(start_row - building_size - 1, start_row - 1, current_col, current_col + building_size, CardinalDirection::CARDINAL_DIRECTION_SOUTH, false, cl_ids, bcf.create_creature_ids(cl_ids), bcf.create_item_ids(cl_ids));
              SettlementGeneratorUtils::generate_building_if_possible(map, bgp, buildings, growth_rate);
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
              vector<ClassIdentifier> cl_ids = bcf.create_house_or_workshop_features(WORKSHOP_PROBABILITY);
              BuildingGenerationParameters bgp(start_row + 1, start_row + building_size + 1, current_col, current_col + building_size, CardinalDirection::CARDINAL_DIRECTION_NORTH, false, cl_ids, bcf.create_creature_ids(cl_ids), bcf.create_item_ids(cl_ids));
              SettlementGeneratorUtils::generate_building_if_possible(map, bgp, buildings, growth_rate);
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
        if (!SettlementGeneratorUtils::does_tile_overlap(map, start_row, current_col) || (probability == 100))
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
  BuildingConfigFactory bcf;

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
              vector<ClassIdentifier> cl_ids = bcf.create_house_or_workshop_features(WORKSHOP_PROBABILITY);
              BuildingGenerationParameters bgp(start_row - building_size - 1, start_row - 1, current_col, current_col + building_size, CardinalDirection::CARDINAL_DIRECTION_SOUTH, false, cl_ids, bcf.create_creature_ids(cl_ids), bcf.create_item_ids(cl_ids));
              SettlementGeneratorUtils::generate_building_if_possible(map, bgp, buildings, growth_rate);
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
              vector<ClassIdentifier> cl_ids = bcf.create_house_or_workshop_features(WORKSHOP_PROBABILITY);
              BuildingGenerationParameters bgp(start_row + 1, start_row + building_size + 1, current_col, current_col + building_size, CardinalDirection::CARDINAL_DIRECTION_NORTH, false, cl_ids, bcf.create_creature_ids(cl_ids), bcf.create_item_ids(cl_ids));
              SettlementGeneratorUtils::generate_building_if_possible(map, bgp, buildings, growth_rate);
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
        if (!SettlementGeneratorUtils::does_tile_overlap(map, start_row, current_col) || (probability == 100))
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

void BaseSettlementGenerator::generate_wells(MapPtr map)
{
  if (map != nullptr)
  {
    TileGenerator tg;
    Dimensions dim = map->size();
    int rows = dim.get_y();
    int cols = dim.get_x();

    for (int i = 0; i < WELLS_MAX; i++)
    {
      for (int j = 0; j < 5; j++)
      {
        int y = RNG::range(0, rows-1);
        int x = RNG::range(0, cols-1);

        TilePtr tile = map->at(y, x);

        // "dig" a well by creating a well and replacing the existing tile.
        if (tile != nullptr && tile->get_tile_type() == TileType::TILE_TYPE_FIELD)
        {
          tile = tg.generate(TileType::TILE_TYPE_WELL);
          map->insert(y, x, tile);

          break;
        }
      }
    }
  }
}

void BaseSettlementGenerator::generate_special_inhabitants(MapPtr map)
{
  if (map != nullptr)
  {
    if (RNG::percent_chance(HIRELING_PROBABILITY))
    {
      Game& game = Game::instance();
      ActionManager& am = game.get_action_manager_ref();

      CreatureGenerationManager cgm;
      CreaturePtr hireling = cgm.generate_follower(am, FollowerType::FOLLOWER_TYPE_HIRELING, RNG::range(CreatureGenerationManager::HIRELING_MIN_LEVEL, CreatureGenerationManager::HIRELING_MAX_LEVEL));
      Dimensions dim = map->size();

      for (int i = 1; i < 20; i++)
      {
        int y = RNG::range(0, dim.get_y() - 1);
        int x = RNG::range(0, dim.get_x() - 1);

        TilePtr tile = map->at(y, x);

        if (tile != nullptr && tile->get_is_available_for_creature(hireling))
        {
          GameUtils::add_new_creature_to_map(game, hireling, map, { y,x });
          break;
        }
      }
    }
  }
}

vector<shared_ptr<SectorFeature>> BaseSettlementGenerator::get_sector_features()
{
  vector<shared_ptr<SectorFeature>> sfs;

  shared_ptr<SectorFeature> sf = std::make_shared<ParkSectorFeature>(0, 0, 100); // no statues or trader - but a pond!
  sfs.push_back(sf);

  sf = std::make_shared<GraveyardSectorFeature>();
  sfs.push_back(sf);

  sf = std::make_shared<LittleLibrarySectorFeature>();
  sfs.push_back(sf);

  sf = std::make_shared<FruitVegetableGardenGenerator>();
  sfs.push_back(sf);

  sf = std::make_shared<OrchardGenerator>();
  sfs.push_back(sf);

  sf = std::make_shared<ShrineSectorFeature>();
  sfs.push_back(sf);

  sf = std::make_shared<TavernSectorFeature>();
  sfs.push_back(sf);

  return sfs;
}