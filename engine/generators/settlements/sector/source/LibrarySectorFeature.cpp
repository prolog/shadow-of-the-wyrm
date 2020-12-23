#include "FeatureDescriptionTextKeys.hpp"
#include "FeatureGenerator.hpp"
#include "Game.hpp"
#include "ItemGenerationManager.hpp"
#include "LibrarySectorFeature.hpp"
#include "RNG.hpp"
#include "SettlementGeneratorUtils.hpp"
#include "TileGenerator.hpp"

using namespace std;

// Regular Library

LibrarySectorFeature::LibrarySectorFeature()
{
}

bool LibrarySectorFeature::generate_interior(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord, const Coordinate& door_coord)
{
  bool generated = false;

  if (map != nullptr)
  {
    vector<Coordinate> corners = { {start_coord.first + 1, start_coord.second + 1}, {start_coord.first + 1, end_coord.second - 1}, {end_coord.first - 1, start_coord.second + 1}, {end_coord.first - 1, end_coord.second - 1} };

    for (const Coordinate& c : corners)
    {
      FeaturePtr fire_pillar = FeatureGenerator::generate_fire_pillar();
      map->at(c)->set_feature(fire_pillar);
    }

    ItemGenerationConstraints igc;
    igc.set_min_danger_level(1);
    igc.set_max_danger_level(5);
    vector<ItemType> itype_restr = { ItemType::ITEM_TYPE_SCROLL, ItemType::ITEM_TYPE_SPELLBOOK };
    igc.set_item_type_restrictions(itype_restr);
    ItemGenerationManager igm;
    ItemGenerationMap imap = igm.generate_item_generation_map(igc);

    Game& game = Game::instance();
    vector<int> feature_rows = { start_coord.first + 1, end_coord.first - 1 };
    std::shuffle(feature_rows.begin(), feature_rows.end(), RNG::get_engine());

    // A few benches, for reading
    int num_benches = RNG::range(2, 4);
    int bench_row = feature_rows.back();
    feature_rows.pop_back();

    for (int i = 0; i < num_benches; i++)
    {
      int cur_col = RNG::range(start_coord.second + 2, end_coord.second - 3);

      if (cur_col == door_coord.second)
      {
        continue;
      }
      else
      {
        FeaturePtr bench = FeatureGenerator::generate_bench();
        map->at({ bench_row, cur_col })->set_feature(bench);
      }
    }

    // Books
    int incr = RNG::range(2, 3);
    int book_row = feature_rows.back();

    for (int col = start_coord.second + 3; col < end_coord.second - 2; col = col + incr)
    {
      if (col == door_coord.second)
      {
        continue;
      }
      else
      {
        ItemPtr generated_item = igm.generate_item(game.get_action_manager_ref(), imap, Rarity::RARITY_COMMON, itype_restr, 0);

        if (generated_item != nullptr)
        {
          map->at({ book_row, col })->get_items()->merge_or_add(generated_item, InventoryAdditionType::INVENTORY_ADDITION_BACK);
        }
      }
    }

    generated = true;
  }

  return generated;
}

bool LibrarySectorFeature::generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  bool generated = false;

  if (map != nullptr)
  {
    vector<Building> buildings;
    CardinalDirection door_dir = static_cast<CardinalDirection>(RNG::range(static_cast<int>(CardinalDirection::CARDINAL_DIRECTION_NORTH), static_cast<int>(CardinalDirection::CARDINAL_DIRECTION_WEST)));
    BuildingGenerationParameters bgp(start_coord.first, end_coord.first, start_coord.second, end_coord.second, door_dir, false, {}, {}, {});
    SettlementGeneratorUtils::generate_building_if_possible(map, bgp, buildings, 100);

    if (!buildings.empty())
    {
      generated = generate_interior(map, start_coord, end_coord, buildings[0].get_door_coord());
    }
  }

  return generated;
}

// Little Library
LittleLibrarySectorFeature::LittleLibrarySectorFeature()
{
}

bool LittleLibrarySectorFeature::generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  bool generated = false;

  if (map != nullptr)
  {
    if (end_coord.first - start_coord.first >= 3 && end_coord.second - start_coord.second >= 5)
    {
      int height = 3;
      int width = 5;

      int start_row = RNG::range(start_coord.first, end_coord.first - height);
      int start_col = RNG::range(start_coord.second, end_coord.second - width);
      int end_row = start_row + 2;

      // Sign
      FeaturePtr sign = FeatureGenerator::generate_sign(SignTextKeys::SIGN_LITTLE_LIBRARY);
      map->at(start_row, start_col)->set_feature(sign);

      // Little library
      vector<Coordinate> corners = { {start_row, start_col + 2}, {start_row, start_col + 4}, {end_row, start_col + 2}, {end_row, start_col + 4} };
      vector<Coordinate> walls = { {start_row + 1, start_col + 2}, {start_row + 1, start_col + 4}, {start_row, start_col + 3}, {end_row, start_col + 3} };
     
      // Remove one of the walls to form an entrance
      std::shuffle(walls.begin(), walls.end(), RNG::get_engine());
      walls.pop_back();

      walls.insert(walls.end(), corners.begin(), corners.end());
      TileGenerator tg;

      for (const Coordinate& c : walls)
      {
        TilePtr wall = tg.generate(TileType::TILE_TYPE_ROCK);
        map->insert(c, wall);
      }

      // Books!
      Coordinate book_c = { start_row + 1, start_col + 3 };
      int num_books = RNG::range(1, 2);
      Game& game = Game::instance();

      ItemGenerationConstraints igc;
      igc.set_min_danger_level(1);
      igc.set_max_danger_level(5);
      vector<ItemType> itype_restr = { ItemType::ITEM_TYPE_SCROLL, ItemType::ITEM_TYPE_SPELLBOOK };
      igc.set_item_type_restrictions(itype_restr);
      ItemGenerationManager igm;
      ItemGenerationMap imap = igm.generate_item_generation_map(igc);

      for (int i = 0; i < num_books; i++)
      {
        ItemPtr generated_item = igm.generate_item(game.get_action_manager_ref(), imap, Rarity::RARITY_COMMON, itype_restr, 0);

        if (generated_item != nullptr)
        {
          map->at(book_c)->get_items()->merge_or_add(generated_item, InventoryAdditionType::INVENTORY_ADDITION_BACK);
        }
      }

      generated = true;
    }
  }

  return generated;
}