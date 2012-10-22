#include "ActionManager.hpp"
#include "EffectFactory.hpp"
#include "ItemFilterFactory.hpp"
#include "ItemIdentifier.hpp"
#include "MessageManager.hpp"
#include "ReadManager.hpp"

using namespace std;
using boost::dynamic_pointer_cast;

// Read a scroll or spellbook.  Scrolls cast a single spell, while
// spellbooks contain spells, and can be used to learn an individual
// spell (the ADOM/nethack model, rather than Angband's/DCSS's).
ActionCostValue ReadManager::read(CreaturePtr creature, ActionManager * const am)
{
  ActionCostValue action_cost_value = 0;

  if (creature && am)
  {
    list<IItemFilterPtr> display_list = ItemFilterFactory::create_readable_filter();
    ItemPtr selected_readable_item = am->inventory(creature, creature->get_inventory(), display_list, false);
    
    if (selected_readable_item)
    {
      ReadablePtr readable = boost::dynamic_pointer_cast<Readable>(selected_readable_item);

      if (readable)
      {
        // Read it - cast or learn the spell
        read_item(creature, am, readable);
        
        // Scroll/spellbook's been read as expected - increment the turn.
        action_cost_value = get_action_cost_value();
      }
    }    
  }

  return action_cost_value;
}

void ReadManager::read_item(CreaturePtr creature, ActionManager * const am, ReadablePtr readable)
{
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
    }
  }
}

void ReadManager::add_read_message(CreaturePtr creature, ReadablePtr readable, const ItemIdentifier& item_id)
{
  if (creature && readable)
  {
    EffectPtr effect = EffectFactory::create_effect(readable->get_effect_type());
    string base_id = readable->get_base_id();
    
    // Get "You/monster reads a scroll lablled "FOO BAR"" message
    string read_message = ActionTextKeys::get_read_message(creature->get_description_sid(), item_id.get_appropriate_usage_description_sid(base_id), creature->get_is_player());
    
    // Display an appropriate message
    MessageManager* manager = MessageManager::instance();
    
    if (manager)
    {
      manager->add_new_message(read_message);
      manager->send();
    }
  }
}

ActionCostValue ReadManager::get_action_cost_value() const
{
  return 1;
}
