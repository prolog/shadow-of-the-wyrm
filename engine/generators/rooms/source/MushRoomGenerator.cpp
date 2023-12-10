#include "MushRoomGenerator.hpp"
#include "ItemManager.hpp"
#include "ItemProperties.hpp"
#include "TileGenerator.hpp"
#include "RNG.hpp"

using namespace std;

const int MushRoomGenerator::PCT_CHANCE_MUSHROOMS = 85;
const int MushRoomGenerator::PCT_CHANCE_SPECIAL_MUSHROOM = 5;

void MushRoomGenerator::generate(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col)
{
  TileGenerator tg;
  vector<string> mushrooms = ItemIdKeys::ITEM_IDS_MUSHROOM;
  vector<string> rare_mushrooms = ItemIdKeys::ITEM_IDS_MUSHROOM_RARE;
  TilePtr tile;

  // Generate mushrooms everywhere.
  for (int i = start_row; i < end_row; i++)
  {
    for (int j = start_col; j < end_col; j++)
    {
      tile = tg.generate(TileType::TILE_TYPE_WEEDS);

      if (RNG::percent_chance(PCT_CHANCE_MUSHROOMS))
      {
        const vector<string>& m_vec = (RNG::percent_chance(PCT_CHANCE_SPECIAL_MUSHROOM) ? rare_mushrooms : mushrooms);
        string m_id = m_vec.at(RNG::range(0, m_vec.size() - 1));
        ItemPtr item = ItemManager::create_item(m_id);

        if (tile != nullptr && item != nullptr)
        {
          tile->get_items()->merge_or_add(item, InventoryAdditionType::INVENTORY_ADDITION_BACK);
        }
      }

      if (tile != nullptr)
      {
        map->insert(i, j, tile);
      }
    }
  }
}
