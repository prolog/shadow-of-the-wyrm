#include "BeerHallSectorFeature.hpp"
#include "CoordUtils.hpp"
#include "FeatureGenerator.hpp"
#include "GeneratorUtils.hpp"
#include "ItemManager.hpp"
#include "RNG.hpp"

using namespace std;

bool BeerHallSectorFeature::generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  bool generated = false;

  if (map != nullptr)
  {
    GeneratorUtils::fill(map, start_coord, end_coord, TileType::TILE_TYPE_DUNGEON);

    vector<string> booze_ids = { ItemIdKeys::ITEM_ID_DRAM_GIN, ItemIdKeys::ITEM_ID_DRAM_MEAD, ItemIdKeys::ITEM_ID_DRAM_WHISKY, ItemIdKeys::ITEM_ID_GNOMISH_STOUT, ItemIdKeys::ITEM_ID_GOBLIN_MOONSHINE, ItemIdKeys::ITEM_ID_ELVEN_BRANDY, ItemIdKeys::ITEM_ID_FORTIFIED_DWARVEN_WINE };
    vector<Coordinate> coords = CoordUtils::get_perimeter_coordinates(start_coord, end_coord);

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
        barrel->set_drinks(RNG::range(10, 30));

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

