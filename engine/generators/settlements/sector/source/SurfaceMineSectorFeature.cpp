#include "SurfaceMineSectorFeature.hpp"
#include "CoordUtils.hpp"
#include "CreatureFactory.hpp"
#include "CreatureGenerationManager.hpp"
#include "CreatureProperties.hpp"
#include "DecisionStrategyProperties.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "GeneratorUtils.hpp"
#include "HostilityManager.hpp"
#include "ItemManager.hpp"
#include "ItemProperties.hpp"
#include "RNG.hpp"

using namespace std;

const int SurfaceMineSectorFeature::PCT_CHANCE_INHABITED = 70;

bool SurfaceMineSectorFeature::generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  bool generated = false;

  if (map != nullptr)
  {
    generate_mine(map, start_coord, end_coord);
    add_excavated_dirt(map, start_coord, end_coord);
    generated = true;
  }

  return generated;
}

void SurfaceMineSectorFeature::generate_mine(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  if (map != nullptr)
  {
    GeneratorUtils::fill(map, start_coord, end_coord, TileType::TILE_TYPE_ROCKY_EARTH);
    vector<string> mine_item_ids = { ItemIdKeys::ITEM_ID_LUMP_GOLD, ItemIdKeys::ITEM_ID_MAGICI_SHARD, ItemIdKeys::ITEM_ID_IRON_INGOT, ItemIdKeys::ITEM_ID_STEEL_INGOT, ItemIdKeys::ITEM_ID_SHOVEL, ItemIdKeys::ITEM_ID_PICK_AXE };

    vector<Coordinate> coords = CoordUtils::get_coordinates_in_range(start_coord, end_coord);
    vector<Coordinate> creature_coords = coords;

    std::shuffle(coords.begin(), coords.end(), RNG::get_engine());
    int num_piles = RNG::range(4, 8);

    for (int i = 0; i < num_piles; i++)
    {
      if (!coords.empty())
      {
        Coordinate c = coords.back();
        int num_items = RNG::range(1, 3);

        for (int j = 0; j < num_items; j++)
        {
          string item_id = mine_item_ids.at(RNG::range(0, mine_item_ids.size() - 1));
          ItemPtr item = ItemManager::create_item(item_id);
          TilePtr tile = map->at(c);

          if (tile != nullptr)
          {
            tile->get_items()->merge_or_add(item, InventoryAdditionType::INVENTORY_ADDITION_BACK);
          }
        }

        coords.pop_back();
      }
    }

    generate_creatures(map, creature_coords);
  }
}

void SurfaceMineSectorFeature::add_excavated_dirt(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  if (map != nullptr)
  {
    vector<Coordinate> border = CoordUtils::get_perimeter_coordinates({ start_coord.first - 1, start_coord.second - 1 }, { end_coord.first + 1, end_coord.second + 1 });
    for (const auto& c : border)
    {
      if (RNG::percent_chance(75))
      {
        TilePtr tile = map->at(c);

        if (tile != nullptr)
        {
          ItemPtr item = ItemManager::create_item(ItemIdKeys::ITEM_ID_DIRT);
          tile->get_items()->merge_or_add(item, InventoryAdditionType::INVENTORY_ADDITION_BACK);
        }
      }
    }
  }
}

void SurfaceMineSectorFeature::generate_creatures(MapPtr map, vector<Coordinate>& creature_coords)
{
  if (map != nullptr)
  {
    if (RNG::percent_chance(PCT_CHANCE_INHABITED))
    {
      Game& game = Game::instance();
      ActionManager& am = game.get_action_manager_ref();
      HostilityManager hm;
      std::shuffle(creature_coords.begin(), creature_coords.end(), RNG::get_engine());

      int num_creatures = 2; // always a pair of miners, for some reason...
      CreatureGenerationManager cgm;
      std::map<string, string> props = { {CreatureProperties::CREATURE_PROPERTIES_MINER, std::to_string(true)} };
      vector<string> c_ids = cgm.get_creature_ids_with_property(CreatureProperties::CREATURE_PROPERTIES_MINER);

      if (!c_ids.empty())
      {
        string miners_id = c_ids.at(RNG::range(0, c_ids.size() - 1));

        for (int i = 0; i < num_creatures; i++)
        {
          if (!creature_coords.empty())
          {
            Coordinate c = creature_coords.back();
            creature_coords.pop_back();

            TilePtr tile = map->at(c);
            CreatureFactory cf;
            CreaturePtr creature = cf.create_by_creature_id(am, miners_id, map);
            
            // The miners are all, for reasons unknown, friendly to the player.
            // They also don't move.
            hm.set_hostility_to_player(creature, false);
            creature->get_decision_strategy()->set_property(DecisionStrategyProperties::DECISION_STRATEGY_SENTINEL, std::to_string(true));

            if (tile && tile->get_is_available_for_creature(creature))
            {
              GameUtils::add_new_creature_to_map(game, creature, map, c);
            }
          }
        }
      }
    }
  }
}
