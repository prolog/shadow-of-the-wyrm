#include "ActionManager.hpp"
#include "ActionTextKeys.hpp"
#include "ConsumableAction.hpp"
#include "EffectFactory.hpp"
#include "Game.hpp"
#include "ItemFilterFactory.hpp"
#include "ItemIdentifier.hpp"
#include "MessageManager.hpp"
#include "QuaffAction.hpp"
#include "SpellFactory.hpp"
#include "SpellShapeProcessorFactory.hpp"
#include "SpellcastingProcessor.hpp"

using namespace std;
using boost::dynamic_pointer_cast;

bool QuaffAction::operator==(const QuaffAction& qm) const
{
  return true;
}

// Select a potion to quaff
ActionCostValue QuaffAction::quaff(CreaturePtr creature, ActionManager * const am)
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
void QuaffAction::quaff_potion(CreaturePtr creature, ActionManager * const am, PotionPtr potion)
{
  if (creature && potion)
  {
    ConsumableAction ca;
    ca.consume(creature, potion);
    
    EffectPtr potion_effect = EffectFactory::create_effect(potion->get_effect_type());
    
    if (potion_effect)
    {
      Game& game = Game::instance();
      MapPtr map = game.get_current_map();
      Coordinate caster_coord = map->get_location(creature->get_id());

      ItemIdentifier item_id;
      string potion_base_id = potion->get_base_id();
      bool potion_originally_identified = item_id.get_item_identified(potion_base_id);

      // Add a message about quaffing.
      add_quaff_message(creature, potion, item_id);
      
      // Reduce the quantity, removing it from the inventory if necessary
      potion->set_quantity(potion->get_quantity() - 1);
      if (potion->get_quantity() == 0) creature->get_inventory().remove(potion->get_id());
      
      // Process the effect using a temporary spell.  This will do any necessary 
      // updates to the creature, and will also add a status message based on
      // whether the item was identified.
      Spell potion_spell = SpellFactory::create_self_targetted_item_spell();
      potion_spell.set_effect(potion->get_effect_type());

      SpellShapeProcessorPtr spell_processor = SpellShapeProcessorFactory::create_processor(potion_spell.get_shape().get_spell_shape_type());
      bool effect_identified = false;

      if (spell_processor)
      {
        // Use the generic spell processor, which is also used for "regular"
        // spellcasting.
        SpellcastingProcessor sp;
        effect_identified = sp.process(spell_processor, creature, map, caster_coord, DIRECTION_NULL, potion_spell);
      }

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

void QuaffAction::add_quaff_message(CreaturePtr creature, PotionPtr potion, const ItemIdentifier& item_id)
{
  EffectPtr effect = EffectFactory::create_effect(potion->get_effect_type());
  string base_id = potion->get_base_id();
  
  // Get "You/monster quaffs a foo-ey potion" message
  string quaff_message = ActionTextKeys::get_quaff_message(creature->get_description_sid(), item_id.get_appropriate_usage_description(potion), creature->get_is_player());
  
  // Display an appropriate message
  MessageManager& manager = MessageManager::instance();
  
  manager.add_new_message(quaff_message);
  manager.send();
}

ActionCostValue QuaffAction::get_action_cost_value() const
{
  return 1;
}
