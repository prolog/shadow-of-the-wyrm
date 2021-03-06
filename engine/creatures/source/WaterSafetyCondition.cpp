#include "WaterSafetyCondition.hpp"
#include "Game.hpp"

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
    Game& game = Game::instance();
    ISeason* season = game.get_current_world()->get_calendar().get_season();

    // Frozen water is safe.
    if (tile->get_is_frozen(season->get_season()))
    {
      return true;
    }
    else
    {
      if (creature->can_breathe(BreatheType::BREATHE_TYPE_WATER) ||
          creature->has_status(StatusIdentifiers::STATUS_ID_FLYING))
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
  }

  return safe;
}
