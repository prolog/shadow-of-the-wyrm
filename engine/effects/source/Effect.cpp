#include "ActionTextKeys.hpp"
#include "Creature.hpp"
#include "Effect.hpp"
#include "Game.hpp"
#include "Serialize.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

Effect::Effect()
: bonus(0)
{
}

void Effect::set_source_id(const string& new_source_id)
{
  source_id = new_source_id;
}

string Effect::get_source_id() const
{
  return source_id;
}

string Effect::get_status_id() const
{
  string no_id;
  return no_id;
}

void Effect::set_bonus(const int new_bonus)
{
  bonus = new_bonus;
}

int Effect::get_bonus() const
{
  return bonus;
}

void Effect::clear_additional_effect_messages()
{
  additional_effect_messages.clear();
}

// Call the correct item effect function based on the item status.  Blessed effects can often be
// much better than uncursed, and cursed are often more hurtful than helpful.
bool Effect::effect(std::shared_ptr<Creature> creature, ActionManager * const am, const ItemStatus item_status, const Coordinate& affected_coordinate, TilePtr affected_tile, const bool show_msg_on_unid) 
{
  bool effect_identified = false;

  switch(item_status)
  {
    case ItemStatus::ITEM_STATUS_BLESSED:
      effect_identified = effect_blessed(creature, am, affected_coordinate, affected_tile);
      break;
    case ItemStatus::ITEM_STATUS_CURSED:
      effect_identified = effect_cursed(creature, am, affected_coordinate, affected_tile);
      break;
    case ItemStatus::ITEM_STATUS_UNCURSED:
    default:
      effect_identified = effect_uncursed(creature, am, affected_coordinate, affected_tile);
      break;
  }
 
  // Display any additional effect messages that only the target of the
  // effect should see.
  if (creature && creature->get_is_player())
  {
    add_additional_effect_messages(creature);
  }

  identify_effect_as_necessary(creature, effect_identified, show_msg_on_unid);

  if (effect_identified && is_negative_effect())
  {
    Game::instance().get_sound(creature)->play(SoundEffectID::NEGATIVE_EFFECT);
  }

  return effect_identified;
}

void Effect::identify_effect_as_necessary(std::shared_ptr<Creature> creature, const bool effect_identified, const bool show_effect_on_unid) const
{
  if (creature)
  {
    if (effect_identified)
    {
      broadcast_effect_message(creature);
    }
    else
    {
      if (show_effect_on_unid)
      {
        inform_unidentified_if_player(creature);
      }
    }
  }
}

void Effect::broadcast_effect_message(std::shared_ptr<Creature> creature) const
{  
  if (creature != nullptr)
  {
    IMessageManager& manager = MMF::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
    string effect_message = get_effect_identification_message(creature);
    
    manager.add_new_message(effect_message);
    manager.send();
  }
}

// Inform the quaffer (if they're the player) that the potion had no discernable effect.
void Effect::inform_unidentified_if_player(std::shared_ptr<Creature> creature) const
{  
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MMF::instance();
    string nothing_happens = StringTable::get(ActionTextKeys::ACTION_NOTHING_HAPPENS);

    manager.add_new_message(nothing_happens);
    manager.send();
  }
}

void Effect::add_additional_effect_messages(CreaturePtr creature) const
{
  IMessageManager& manager = MMF::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

  for (const string& msg : additional_effect_messages)
  {
    if (!msg.empty())
    {
      manager.add_new_message(StringTable::get(msg));
    }
  }

  manager.send();
}

bool Effect::is_negative_effect() const
{
  return false;
}

void Effect::read_properties(const map<string, string>& /*properties*/)
{
}

void Effect::set_originator(CreaturePtr new_originator)
{
  originator = new_originator;
}

CreaturePtr Effect::get_originator() const
{
  return originator;
}