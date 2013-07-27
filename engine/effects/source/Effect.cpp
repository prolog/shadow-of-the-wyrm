#include <boost/foreach.hpp>
#include "ActionTextKeys.hpp"
#include "Creature.hpp"
#include "Effect.hpp"
#include "Serialize.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

// Call the correct item effect function based on the item status.  Blessed effects can often be
// much better than uncursed, and cursed are often more hurtful than helpful.
bool Effect::effect(boost::shared_ptr<Creature> creature, ActionManager * const am, const ItemStatus item_status) 
{
  bool effect_identified = false;

  switch(item_status)
  {
    case ITEM_STATUS_BLESSED:
      effect_identified = effect_blessed(creature, am);
      break;
    case ITEM_STATUS_CURSED:
      effect_identified = effect_cursed(creature, am);
      break;
    case ITEM_STATUS_UNCURSED:
    default:
      effect_identified = effect_uncursed(creature, am);
      break;
  }
 
  // Display any additional effect messages that only the target of the
  // effect should see.
  if (creature && creature->get_is_player())
  {
    add_additional_effect_messages(creature);
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
  IMessageManager& manager = MessageManagerFactory::instance(creature);
  
  if (creature && creature->get_is_player())
  {
    string effect_message = get_effect_identification_message(creature);
    
    manager.add_new_message(effect_message);
    manager.send();
  }
}

// Inform the quaffer (if they're the player) that the potion had no discernable effect.
void Effect::inform_unidentified_if_player(boost::shared_ptr<Creature> creature) const
{
  IMessageManager& manager = MessageManagerFactory::instance(creature);
  
  if (creature && creature->get_is_player())
  {
    string nothing_happens = StringTable::get(ActionTextKeys::ACTION_NOTHING_HAPPENS);

    manager.add_new_message(nothing_happens);
    manager.send();
  }
}

void Effect::add_additional_effect_messages(CreaturePtr creature) const
{
  BOOST_FOREACH(AdditionalEffectMessagePtr msg, additional_effect_messages)
  {
    if (msg)
    {
      msg->add_effect_message(creature);
    }
  }
}

