#include "Conversion.hpp"
#include "ShopUtils.hpp"
#include "Tile.hpp"

using namespace std;

string ShopUtils::generate_shop_id_from_shopkeeper_name(const string& shopkeeper_name)
{
  string s_lower = String::to_lower(shopkeeper_name);
  string shop_id = s_lower + "_shop";
  return shop_id;
}

bool ShopUtils::has_space_for_wares(MapPtr map, const Shop& shop)
{
  Coordinate start = shop.get_start();
  Coordinate end = shop.get_end();

  // Check the interior. For each tile, if there are unpaid (ie shop-owned)
  // items, skip it. If there's a tile without unpaid items, there's space.
  for (int row = start.first; row <= end.first; row++)
  {
    for (int col = start.second; col <= end.second; col++)
    {
      // Are there any unpaid items here?  If so, skip item generation
      // for that tile.
      TilePtr tile = map->at(row, col);

      if (tile)
      {
        IInventoryPtr items = tile->get_items();

        if (items != nullptr && items->has_unpaid_items() == false)
        {
          return true;
        }
      }
    }
  }

  return false;
}

#ifdef UNIT_TESTS
#include "unit_tests/ShopUtils_test.cpp"
#endif

