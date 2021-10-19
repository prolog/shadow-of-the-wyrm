#include "DenseVegetationSectorFeature.hpp"
#include "ItemManager.hpp"
#include "RNG.hpp"
#include "TileGenerator.hpp"

using namespace std;

DenseVegetationSectorFeature::DenseVegetationSectorFeature(const vector<TileType>& new_base_terrain_types, const vector<string>& new_item_ids, const int new_pct_chance_item)
: base_terrain_types(new_base_terrain_types), item_ids(new_item_ids), pct_chance_item(new_pct_chance_item)
{
}

bool DenseVegetationSectorFeature::generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord)
{
  bool generated = false;

  if (!base_terrain_types.empty())
  {
    TileGenerator tg;
    TilePtr tile;
    ItemPtr item;

    for (int row = start_coord.first; row <= end_coord.first; row++)
    {
      for (int col = start_coord.second; col <= end_coord.second; col++)
      {
        tile = tg.generate(base_terrain_types[RNG::range(0, base_terrain_types.size() - 1)]);

        if (tile != nullptr)
        {
          if (!item_ids.empty() && RNG::percent_chance(pct_chance_item))
          {
            string item_id = item_ids[RNG::range(0, item_ids.size() - 1)];
            item = ItemManager::create_item(item_id);

            tile->get_items()->merge_or_add(item, InventoryAdditionType::INVENTORY_ADDITION_BACK);
          }

          map->insert({ row, col }, tile);
        }
      }
    }

    generated = true;
  }

  return generated;
}
