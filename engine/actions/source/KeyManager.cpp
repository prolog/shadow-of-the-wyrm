#include <boost/foreach.hpp>
#include "KeyManager.hpp"
#include "ItemManager.hpp"
#include "Tool.hpp"

using namespace std;

// Check a creature's equipment and inventory to see if it has a tool that has a lock_id
// equal to the lock's, assuming the lock's value is non-empty.
bool KeyManager::has_key(CreaturePtr creature, LockPtr lock)
{
  if (creature && lock)
  {
    string lock_id = lock->get_lock_id();

    if (!lock_id.empty())
    {
      list<ItemPtr> tools = ItemManager::get_items_by_type(creature, ITEM_TYPE_TOOL);

      BOOST_FOREACH(ItemPtr item, tools)
      {
        if (item)
        {
          ToolPtr tool = boost::dynamic_pointer_cast<Tool>(item);

          if (tool && (tool->get_lock_id() == lock_id))
          {
            return true;
          }
        }
      }
    }
  }

  return false;
}

ActionCostValue KeyManager::get_action_cost_value() const
{
  return 1;
}

