#include "Creature.hpp"
#include "Effect.hpp"
#include "StringConstants.hpp"
#include "MessageManager.hpp"

using std::string;

// Call the correct item effect function based on the item status.  Blessed effects can often be
// much better than uncursed, and cursed are often more hurtful than helpful.
bool Effect::effect(boost::shared_ptr<Creature> creature, const ItemStatus item_status) const
{
  bool effect_identified = false;

  switch(item_status)
  {
    case ITEM_STATUS_BLESSED:
      effect_identified = effect_blessed(creature);
      break;
    case ITEM_STATUS_CURSED:
      effect_identified = effect_cursed(creature);
      break;
    case ITEM_STATUS_UNCURSED:
    default:
      effect_identified = effect_uncursed(creature);
      break;
  }
  
  identify_effect_as_necessary(creature, effect_identified);

  return effect_identified;
}

void Effect::identify_effect_as_necessary(boost::shared_ptr<Creature> creature, const bool effect_identified) const
{
  if (creature)
  {
    if (effect_identified)
    {
      identify_effect_if_player(creature);

      // if (!creature->get_is_player()) {
      // JCD FIXME: Do some sort of "broadcasting" thing here, so that nearby creatures can learn about the
      // potion's effect.
      // }
    }
    else
    {
      inform_unidentified_if_player(creature);
    }
  }
}

void Effect::identify_effect_if_player(boost::shared_ptr<Creature> creature) const
{
  MessageManager* manager = MessageManager::instance();
  
  if (manager && creature && creature->get_is_player())
  {
    string effect_message = get_effect_identification_message(creature);
    
    manager->add_new_message(effect_message);
    manager->send();
  }
}

// Inform the quaffer (if they're the player) that the potion had no discernable effect.
void Effect::inform_unidentified_if_player(boost::shared_ptr<Creature> creature) const
{
  MessageManager* manager = MessageManager::instance();
  
  if (manager && creature && creature->get_is_player())
  {
    string nothing_happens = StringTable::get(ActionTextKeys::ACTION_NOTHING_HAPPENS);

    manager->add_new_message(nothing_happens);
    manager->send();
  }
}
