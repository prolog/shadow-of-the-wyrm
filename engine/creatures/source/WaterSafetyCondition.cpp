#include "WaterSafetyCondition.hpp"

using namespace std;

// A water tile is safe if the creature breathes water, flies, or the creature 
// has a boat.
//
// Incorporeal creatures aren't safe crossing water: air-breathing creatures
// still need to breathe, and spirits (for reasons unknown) do not seem to
// be able to cross water...
bool WaterSafetyCondition::is_safe(CreaturePtr creature, TilePtr tile)
{
  bool safe = false;

  if (creature)
  {
    if ((creature->get_breathes() == BreatheType::BREATHE_TYPE_WATER) || (creature->has_status(StatusIdentifiers::STATUS_ID_FLYING)))
    {
      safe = true;
    }
    else
    {
      IInventoryPtr inv = creature->get_inventory();
      const list<ItemPtr> items = inv->get_items_cref();

      for (ItemPtr item : items)
      {
        if (item && item->get_type() == ItemType::ITEM_TYPE_BOAT)
        {
          safe = true;
          break;
        }
      }
    }
  }

  return safe;
}
