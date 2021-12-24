#include "BuildingConfigFactory.hpp"
#include "MapUtils.hpp"
#include "RNG.hpp"
#include "SettlementGeneratorUtils.hpp"
#include "StorehouseSectorFeature.hpp"

using namespace std;

StorehouseSectorFeature::StorehouseSectorFeature()
{
}

bool StorehouseSectorFeature::generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  bool generated = false;

  if (map != nullptr)
  {
    vector<Building> buildings;
    vector<CardinalDirection> door_dirs = MapUtils::get_unblocked_door_dirs(map, start_coord, end_coord);
    CardinalDirection door_dir = static_cast<CardinalDirection>(RNG::range(0, door_dirs.size()-1));
    BuildingConfigFactory bcf;
    vector<string> selection_items = { ItemIdKeys::ITEM_ID_VEGETABLE_1, ItemIdKeys::ITEM_ID_VEGETABLE_2, ItemIdKeys::ITEM_ID_VEGETABLE_3, ItemIdKeys::ITEM_ID_VEGETABLE_4, ItemIdKeys::ITEM_ID_VEGETABLE_5, ItemIdKeys::ITEM_ID_VEGETABLE_6, ItemIdKeys::ITEM_ID_SALMON, ItemIdKeys::ITEM_ID_CARP, ItemIdKeys::ITEM_ID_TROUT, ItemIdKeys::ITEM_ID_COD, ItemIdKeys::ITEM_ID_TUNA };
    vector<string> potential_rare = { ItemIdKeys::ITEM_ID_VERBENA, ItemIdKeys::ITEM_ID_WHITE_BASIL, ItemIdKeys::ITEM_ID_WHITEFLOWER, ItemIdKeys::ITEM_ID_VOXFLOWER, ItemIdKeys::ITEM_ID_STONEFLOWER };

    vector<string> item_ids;
    auto items_to_gen = selection_items.size() * 2;

    for (size_t i = 1; i < items_to_gen; i++)
    {
      string item = selection_items.at(RNG::range(0, selection_items.size() - 1));
      int num_items = RNG::range(1, 4);

      for (int j = 0; j < num_items; j++)
      {
        item_ids.push_back(item);
      }
    }

    for (const auto& rare_id : potential_rare)
    {
      if (RNG::percent_chance(50))
      {
        item_ids.push_back(rare_id);
      }
    }

    vector<ClassIdentifier> cl_ids = bcf.create_house_features();
    BuildingGenerationParameters bgp(start_coord.first, end_coord.first, start_coord.second, end_coord.second, door_dir, false, {}, {}, item_ids);
    SettlementGeneratorUtils::generate_building_if_possible(map, bgp, buildings, 100, false);
  }

  return generated;
}

