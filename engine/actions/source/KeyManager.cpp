#include "KeyManager.hpp"
#include "ItemManager.hpp"
#include "Tool.hpp"

using namespace std;

const string KeyManager::SKELETON_KEY_ID = "*";

// Check a creature's equipment and inventory to see if it has a tool that has a lock_id
// equal to the lock's, assuming the lock's value is non-empty.
bool KeyManager::has_key(CreaturePtr creature, LockPtr lock)
{
  if (creature && lock)
  {
    string lock_id = lock->get_lock_id();

    if (!lock_id.empty())
    {
      const list<ItemPtr> tools = creature->get_inventory()->get_items_cref();

      for(ItemPtr item : tools)
      {
        if (item)
        {
          string item_lock_id = item->get_lock_id();
          if (item && ((item_lock_id == lock_id) || (item_lock_id == SKELETON_KEY_ID)))
          {
            return true;
          }
        }
      }
    }
  }

  return false;
}

ActionCostValue KeyManager::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}

