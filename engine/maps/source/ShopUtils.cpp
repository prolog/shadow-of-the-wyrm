#include "Conversion.hpp"
#include "CoordUtils.hpp"
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

// A shop should have a maximum of one unpaid item stack per tile.  When shops
// start off, these will be distributed evenly, but the maximum should stay in
// place so that crafty players can't just pick up all the items and move them
// to a particular tile and get a full repop.
uint ShopUtils::get_max_unpaid_items_for_repop(const Coordinate& start, const Coordinate& end)
{
  // Say we've got tiles going from (14,26) to (15,30) - ie, the Isen Dun shop. Even though
  // the height is 1 (15-14), there are two rows to fill, and even though the width is 4
  // (30-26), there are 5 columns to fill. So, add 1 to each to get the actual number of
  // tiles, rather than just the height/width.
  return (1 + CoordUtils::get_width(start, end)) * (1 + CoordUtils::get_height(start, end));
}

uint ShopUtils::get_num_unpaid_stacks(MapPtr map, const Coordinate& start, const Coordinate& end)
{
  uint stacks = 0;
  TilePtr tile;

  if (map != nullptr)
  {
    for (int y = start.first; y <= end.first; y++)
    {
      for (int x = start.second; x <= end.second; x++)
      {
        tile = map->at(y, x);

        if (tile != nullptr)
        {
          stacks += tile->get_items()->count_unpaid_item_stacks();
        }
      }
    }
  }

  return stacks;
}


#ifdef UNIT_TESTS
#include "unit_tests/ShopUtils_test.cpp"
#endif

