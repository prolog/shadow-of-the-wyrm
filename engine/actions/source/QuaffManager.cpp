#include "ActionManager.hpp"
#include "ConsumableManager.hpp"
#include "ItemDisplayFilterFactory.hpp"
#include "QuaffManager.hpp"

using std::list;
using boost::dynamic_pointer_cast;

// Select a potion to quaff
ActionCostValue QuaffManager::quaff(CreaturePtr creature, ActionManager * const am)
{
  ActionCostValue action_cost_value = 0;
  
  if (creature)
  {
    list<IItemDisplayFilterPtr> display_filter_list = ItemDisplayFilterFactory::create_item_type_filter(ITEM_TYPE_POTION);
    ItemPtr selected_item = am->inventory(creature, creature->get_inventory(), display_filter_list, false);
    
    if (selected_item)
    {
      PotionPtr potion = dynamic_pointer_cast<Potion>(selected_item);
      
      if (potion)
      {
        quaff_potion(creature, potion);
        action_cost_value = get_action_cost_value();
      }
    }
  }
  
  return action_cost_value;
}

// A valid potion's been selected.  Quaff it: get the potion's nutrition, and then do the magical effect.
void QuaffManager::quaff_potion(CreaturePtr creature, PotionPtr potion)
{
  if (creature && potion)
  {
    ConsumableManager cm;
    cm.consume(creature, potion);
    
    EffectPtr potion_effect = potion->get_effect();
    
    if (potion_effect)
    {
      bool effect_identified = potion_effect->effect(creature, potion->get_status());
      
      if (effect_identified /* || potion->get_item_identified() */)
      {
        // JCD FIXME: Identify the item in the master list.
      }
    }
  }
}

ActionCostValue QuaffManager::get_action_cost_value() const
{
  return 1;
}
