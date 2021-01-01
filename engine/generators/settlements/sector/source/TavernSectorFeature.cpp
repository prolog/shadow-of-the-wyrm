#include "CoordUtils.hpp"
#include "CreatureFeatures.hpp"
#include "CreatureGenerationManager.hpp"
#include "FeatureDescriptionTextKeys.hpp"
#include "FeatureGenerator.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "ItemManager.hpp"
#include "RNG.hpp"
#include "SettlementGeneratorUtils.hpp"
#include "TavernSectorFeature.hpp"
#include "WildflowerGardenGenerator.hpp"

using namespace std;

const int TavernSectorFeature::MIN_HEIGHT_FOR_BARRELS = 5;

bool TavernSectorFeature::generate_feature(MapPtr map, const Coordinate& st_coord, const Coordinate& end_coord)
{
  bool generated = false;
  int height = end_coord.first - st_coord.first;
  Coordinate start_coord = st_coord;
  bool create_barrels = false;

  if (map != nullptr)
  {
    if (height >= MIN_HEIGHT_FOR_BARRELS)
    {
      create_barrels = true;
      start_coord.first += 1;
    }

    vector<Building> buildings;
    vector<ClassIdentifier> feature_ids;
    int num_tables = RNG::range(2, 4);

    for (int i = 0; i < num_tables; i++)
    {
      feature_ids.push_back(ClassIdentifier::CLASS_ID_TABLE);

      if (RNG::percent_chance(40))
      {
        feature_ids.push_back(ClassIdentifier::CLASS_ID_BENCH);
      }
    }

    vector<string> creature_ids = { CreatureID::CREATURE_ID_BARTENDER };

    int num_drunks = RNG::range(1, 2);
    for (int i = 0; i < num_drunks; i++)
    {
      creature_ids.push_back(CreatureID::CREATURE_ID_DRUNK);
    }

    vector<string> item_ids = { ItemIdKeys::ITEM_ID_DRAM_WHISKY, ItemIdKeys::ITEM_ID_GNOMISH_STOUT };

    CardinalDirection door_dir = static_cast<CardinalDirection>(RNG::range(static_cast<int>(CardinalDirection::CARDINAL_DIRECTION_NORTH), static_cast<int>(CardinalDirection::CARDINAL_DIRECTION_WEST)));
    BuildingGenerationParameters bgp(start_coord.first, end_coord.first, start_coord.second, end_coord.second, door_dir, false, feature_ids, creature_ids, item_ids);
    SettlementGeneratorUtils::generate_building_if_possible(map, bgp, buildings, 100);
    CreatureGenerationManager cgm;
    Game& game = Game::instance();

    if (!buildings.empty())
    {
      generated = true;

      // Now, generate adventurers
      int num_adv = RNG::range(1, 2);

      Building b = buildings[0];
      pair<Coordinate, Coordinate> interior = b.get_interior_coords();
      Coordinate dc = b.get_door_coord();

      for (int i = 0; i < num_adv; i++)
      {
        for (int j = 0; j < 5; j++)
        {
          Coordinate c = { RNG::range(interior.first.first, interior.second.first), RNG::range(interior.first.second, interior.second.second) };
          TilePtr tile = map->at(c);

          if (tile != nullptr && !tile->has_creature())
          {
            CreaturePtr adv = cgm.generate_follower(game.get_action_manager_ref(), FollowerType::FOLLOWER_TYPE_ADVENTURER, 1);
            GameUtils::add_new_creature_to_map(game, adv, map, c);

            break;
          }
        }
      }

      // Generate a sign
      vector<Coordinate> sign_locs = { CoordUtils::get_new_coordinate(dc, Direction::DIRECTION_NORTH_WEST), CoordUtils::get_new_coordinate(dc, Direction::DIRECTION_SOUTH_EAST) };
      for (const Coordinate& c : sign_locs)
      {
        TilePtr tile = map->at(c);

        if (tile != nullptr && tile->get_tile_type() != TileType::TILE_TYPE_DUNGEON && tile->get_movement_multiplier() > 0 && !tile->has_feature())
        {
          FeaturePtr sign = FeatureGenerator::generate_sign(SignTextKeys::SIGN_TAVERN);
          tile->set_feature(sign);

          break;
        }
      }

      // Barrels go along the north wall - this gets the least sun
      if (create_barrels)
      {
        generate_barrels(map, st_coord, end_coord, buildings[0]);
      }
    }
  }

  return generated;
}

void TavernSectorFeature::generate_barrels(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const Building& building)
{
  if (map != nullptr)
  {
    vector<string> item_ids = { ItemIdKeys::ITEM_ID_GNOMISH_STOUT, ItemIdKeys::ITEM_ID_ELVEN_BRANDY, ItemIdKeys::ITEM_ID_DRAM_MEAD, ItemIdKeys::ITEM_ID_DRAM_GIN };
    int incr_mod = RNG::range(1, 3);
    WildflowerGardenGenerator wgg;
    ItemManager im;

    auto flower_details = wgg.get_wildflower_details();

    for (int col = start_coord.second; col <= end_coord.second; col++)
    {
      TilePtr tile = map->at(start_coord.first, col);

      if (tile != nullptr && !tile->has_feature())
      {
        if (col % incr_mod == 0 && col != building.get_door_coord().second)
        {
          // Generate a barrel.
          FeaturePtr bfeat = FeatureGenerator::generate_barrel();
          std::shared_ptr<Barrel> barrel = dynamic_pointer_cast<Barrel>(bfeat);

          if (barrel != nullptr)
          {
            barrel->set_pour_item_id(item_ids[RNG::range(0, item_ids.size() - 1)]);
            tile->set_feature(barrel);
          }
        }
        else
        {
          // Generate flowers between the barrels.
          string wildflower_id = flower_details.second[RNG::range(flower_details.first.first, flower_details.first.second)];
          ItemPtr wildflower = im.create_item(wildflower_id);
          tile->get_items()->merge_or_add(wildflower, InventoryAdditionType::INVENTORY_ADDITION_BACK);
        }
      }
    }
  }
}
