#include "WaterSafetyCondition.hpp"

using namespace std;

// A water tile is safe only if the creature has a boat.
//
// After all, some creatures can swim, some even can swim well, but there
// are no creatures (not yet, anyway) that can swim indefinitely.
bool WaterSafetyCondition::is_safe(CreaturePtr creature, TilePtr tile)
{
  bool safe = false;

  if (creature)
  {
    if (creature->get_breathes() == BREATHE_TYPE_WATER)
    {
      safe = true;
    }
    else
    {
      Inventory& inv = creature->get_inventory();
      const list<ItemPtr> items = inv.get_items_cref();

      for (ItemPtr item : items)
      {
        if (item && item->get_type() == ITEM_TYPE_BOAT)
        {
          safe = true;
          break;
        }
      }
    }
  }

  return safe;
}
