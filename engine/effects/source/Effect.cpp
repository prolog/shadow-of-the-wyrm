#include <boost/foreach.hpp>
#include "AdditionalEffectMessageFactory.hpp"
#include "Creature.hpp"
#include "Effect.hpp"
#include "Serialize.hpp"
#include "StringConstants.hpp"
#include "MessageManager.hpp"

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
    add_additional_effect_messages();
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

void Effect::add_additional_effect_messages() const
{
  BOOST_FOREACH(AdditionalEffectMessagePtr msg, additional_effect_messages)
  {
    if (msg)
    {
      msg->add_effect_message();
    }
  }
}

bool Effect::serialize(ostream& stream)
{
  Serialize::write_size_t(stream, additional_effect_messages.size());

  BOOST_FOREACH(AdditionalEffectMessagePtr message, additional_effect_messages)
  {
    if (message)
    {
      Serialize::write_class_id(stream, message->get_class_identifier());
      message->serialize(stream);
    }
    else
    {
      Serialize::write_class_id(stream, CLASS_ID_NULL);
    }
  }

  return true;
}

bool Effect::deserialize(istream& stream)
{
  size_t messages_size = 0;
  Serialize::read_size_t(stream, messages_size);

  for (unsigned int i = 0; i < messages_size; i++)
  {
    ClassIdentifier cl_id = CLASS_ID_NULL;
    Serialize::read_class_id(stream, cl_id);

    if (cl_id != CLASS_ID_NULL)
    {
      AdditionalEffectMessagePtr message = AdditionalEffectMessageFactory::create_additional_effect_message(cl_id);
      if (!message) return false;
      if (!message->deserialize(stream)) return false;

      additional_effect_messages.push_back(message);
    }
  }
  return true;
}
