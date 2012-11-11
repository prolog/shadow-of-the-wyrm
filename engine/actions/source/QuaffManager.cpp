#include "ActionManager.hpp"
#include "ConsumableManager.hpp"
#include "EffectFactory.hpp"
#include "ItemFilterFactory.hpp"
#include "ItemIdentifier.hpp"
#include "MessageManager.hpp"
#include "QuaffManager.hpp"

using namespace std;
using boost::dynamic_pointer_cast;

bool QuaffManager::operator==(const QuaffManager& qm)
{
  return true;
}

// Select a potion to quaff
ActionCostValue QuaffManager::quaff(CreaturePtr creature, ActionManager * const am)
{
  ActionCostValue action_cost_value = 0;
  
  if (creature)
  {
    list<IItemFilterPtr> display_filter_list = ItemFilterFactory::create_item_type_filter(ITEM_TYPE_POTION);
    ItemPtr selected_item = am->inventory(creature, creature->get_inventory(), display_filter_list, false);
    
    if (selected_item)
    {
      PotionPtr potion = dynamic_pointer_cast<Potion>(selected_item);
      
      if (potion)
      {
        quaff_potion(creature, am, potion);
        action_cost_value = get_action_cost_value();
      }
    }
  }
  
  return action_cost_value;
}

// A valid potion's been selected.  Quaff it: get the potion's nutrition, and then do the magical effect.
void QuaffManager::quaff_potion(CreaturePtr creature, ActionManager * const am, PotionPtr potion)
{
  if (creature && potion)
  {
    ConsumableManager cm;
    cm.consume(creature, potion);
    
    EffectPtr potion_effect = EffectFactory::create_effect(potion->get_effect_type());
    
    if (potion_effect)
    {
      ItemIdentifier item_id;
      string potion_base_id = potion->get_base_id();
      bool potion_originally_identified = item_id.get_item_identified(potion_base_id);

      // Add a message about quaffing.
      add_quaff_message(creature, potion, item_id);
      
      // Reduce the quantity, removing it from the inventory if necessary
      potion->set_quantity(potion->get_quantity() - 1);
      if (potion->get_quantity() == 0) creature->get_inventory().remove(potion->get_id());
      
      // Process the effect.  This will do any necessary updates to the creature, and will also
      // add a status message based on whether the item was identified.
      bool effect_identified = potion_effect->effect(creature, am, potion->get_status());
      
      // Was the item identified?
      if (effect_identified)
      {        
        // If the item was not identified prior to quaffing, identify it now.
        if (!potion_originally_identified)
        {
          item_id.set_item_identified(potion, potion_base_id, true);
        }
      }
    }
  }
}

void QuaffManager::add_quaff_message(CreaturePtr creature, PotionPtr potion, const ItemIdentifier& item_id)
{
  EffectPtr effect = EffectFactory::create_effect(potion->get_effect_type());
  string base_id = potion->get_base_id();
  
  // Get "You/monster quaffs a foo-ey potion" message
  string quaff_message = ActionTextKeys::get_quaff_message(creature->get_description_sid(), item_id.get_appropriate_usage_description_sid(base_id), creature->get_is_player());
  
  // Display an appropriate message
  MessageManager* manager = MessageManager::instance();
  
  if (manager)
  {
    manager->add_new_message(quaff_message);
    manager->send();
  }
}

ActionCostValue QuaffManager::get_action_cost_value() const
{
  return 1;
}
