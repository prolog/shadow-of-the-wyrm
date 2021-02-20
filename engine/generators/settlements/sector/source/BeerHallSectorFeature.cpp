#include "BeerHallSectorFeature.hpp"
#include "BuildingConfigFactory.hpp"
#include "BuildingGenerationParameters.hpp"
#include "Building.hpp"
#include "CoordUtils.hpp"
#include "FeatureGenerator.hpp"
#include "GeneratorUtils.hpp"
#include "ItemManager.hpp"
#include "RNG.hpp"
#include "SettlementGeneratorUtils.hpp"

using namespace std;

BeerHallSectorFeature::BeerHallSectorFeature()
: generate_walls(false)
{
}

BeerHallSectorFeature::BeerHallSectorFeature(const bool new_generate_walls)
: generate_walls(new_generate_walls)
{
}

bool BeerHallSectorFeature::generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  bool generated = false;
  
  Coordinate interior_start = start_coord;
  Coordinate interior_end = end_coord;

  if (generate_walls)
  {
    CardinalDirection door_dir = static_cast<CardinalDirection>(RNG::range(static_cast<int>(CardinalDirection::CARDINAL_DIRECTION_NORTH), static_cast<int>(CardinalDirection::CARDINAL_DIRECTION_WEST)));
    BuildingConfigFactory bcf;
    BuildingGenerationParameters bgp(start_coord.first, end_coord.first, start_coord.second, end_coord.second, door_dir, false, bcf.create_shop_features(), bcf.create_shop_creature_ids(), bcf.create_shop_item_ids());

    vector<Building> buildings;
    generated = SettlementGeneratorUtils::generate_building_if_possible(map, bgp, buildings, 100);

    interior_start = {start_coord.first+1, start_coord.second+1};
    interior_end = {end_coord.first-1, end_coord.second-1};
  }

  if (map != nullptr)
  {
    // When we generate a building, we also generate the floor - no need to
    // call this twice.
    if (generate_walls == false)
    {
      GeneratorUtils::fill(map, interior_start, interior_end, TileType::TILE_TYPE_DUNGEON);
    }

    vector<string> booze_ids = { ItemIdKeys::ITEM_ID_DRAM_GIN, 
                                 ItemIdKeys::ITEM_ID_DRAM_MEAD, 
                                 ItemIdKeys::ITEM_ID_DRAM_WHISKY, 
                                 ItemIdKeys::ITEM_ID_GNOMISH_STOUT, 
                                 ItemIdKeys::ITEM_ID_GOBLIN_MOONSHINE, 
                                 ItemIdKeys::ITEM_ID_ELVEN_BRANDY, 
                                 ItemIdKeys::ITEM_ID_FORTIFIED_DWARVEN_WINE, 
                                 ItemIdKeys::ITEM_ID_HEALING_POTION, 
                                 ItemIdKeys::ITEM_ID_ETHER_POTION, 
                                 ItemIdKeys::ITEM_ID_UNSTONING_POTION };

    vector<Coordinate> coords = CoordUtils::get_perimeter_coordinates(interior_start, interior_end);

    // Place barrels or place booze around the perimeter.
    for (const Coordinate& c : coords)
    {
      bool create_barrel = RNG::percent_chance(33);
      string booze_id = booze_ids.at(RNG::range(0, booze_ids.size() - 1));
      TilePtr tile = map->at(c);

      if (create_barrel)
      {
        FeaturePtr barrel_f = FeatureGenerator::generate_barrel();
        shared_ptr<Barrel> barrel = dynamic_pointer_cast<Barrel>(barrel_f);

        barrel->set_tap(true);
        barrel->set_pour_item_id(booze_id);
        barrel->set_drinks(RNG::range(5, 10));

        if (tile && !tile->has_feature())
        {
          tile->set_feature(barrel);
        }
      }
      else
      {
        ItemPtr booze = ItemManager::create_item(booze_id);

        if (booze != nullptr && tile != nullptr)
        {
          tile->get_items()->merge_or_add(booze, InventoryAdditionType::INVENTORY_ADDITION_BACK);
        }
      }
    }

    generated = true;
  }

  return generated;
}

