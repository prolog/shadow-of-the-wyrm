#include "EffectFactory.hpp"
#include "ItemIdentifier.hpp"
#include "MessageManager.hpp"
#include "ScrollReadStrategy.hpp"

using namespace std;

ActionCostValue ScrollReadStrategy::read(CreaturePtr creature, ActionManager * const am, ReadablePtr readable)
{
  ActionCostValue acv = 0;

  if (creature && readable)
  {
    EffectPtr spell_effect = EffectFactory::create_effect(readable->get_effect_type());
    
    if (spell_effect)
    {
      ItemIdentifier item_id;
      string base_id = readable->get_base_id();
      bool readable_originally_identified = item_id.get_item_identified(base_id);
      
      // Add a message about what's being read
      add_read_message(creature, readable, item_id);
      
      // Destroy the item if applicable.
      if (readable->destroy_on_read())
      {
        readable->set_quantity(readable->get_quantity() - 1);
        if (readable->get_quantity() == 0) creature->get_inventory().remove(readable->get_id());
      }
      
      // Was the effect identified?  If it was, and if the item wasn't previously identified,
      // identify the item in the item templates.
      bool effect_identified = spell_effect->effect(creature, am, readable->get_status());      
      if (effect_identified && !readable_originally_identified)
      {
        item_id.set_item_identified(readable, base_id, true);
      }

      acv = get_action_cost_value();
    }
  }

  return acv;
}

ActionCostValue ScrollReadStrategy::get_action_cost_value() const
{
  return 1;
}

