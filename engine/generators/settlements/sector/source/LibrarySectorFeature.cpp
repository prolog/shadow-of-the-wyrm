#include "FeatureGenerator.hpp"
#include "Game.hpp"
#include "ItemGenerationManager.hpp"
#include "LibrarySectorFeature.hpp"
#include "RNG.hpp"
#include "SettlementGeneratorUtils.hpp"

using namespace std;

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

