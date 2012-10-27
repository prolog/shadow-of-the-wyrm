#include "ActionManager.hpp"
#include "FoodManager.hpp"
#include "ItemFilterFactory.hpp"

using std::list;

FoodManager::FoodManager()
{
}

// Try to eat something.  First check the inventory, and warn the player
// if there is nothing edible (this costs 0).  Otherwise, bring up the
// inventory, and filter by items of ITEM_TYPE_FOOD and ITEM_TYPE_PLANT.
// If the user selects nothing in this case, the action cost should still
// be 0; otherwise, it should count as a spent action.
ActionCostValue FoodManager::eat(CreaturePtr creature, ActionManager * const am)
{
  ActionCostValue action_cost_value = 0;

  if (creature)
  {
    list<IItemFilterPtr> display_list = ItemFilterFactory::create_edible_filter();
    ItemPtr selected_edible_item = am->inventory(creature, creature->get_inventory(), display_list, false);
    
    if (selected_edible_item)
    {
      // Try to eat the item
      int x = 1;

      // The item has been eaten.  Advance the turn:
      action_cost_value = get_action_cost_value();
    }    
  }

  return action_cost_value;
}

ActionCostValue FoodManager::get_action_cost_value() const
{
  return 1;
}

