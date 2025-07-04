#include "ActionTextKeys.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "CarryingCapacityCalculator.hpp"
#include "ItemProperties.hpp"
#include "MessageManagerFactory.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

// Check to see if the creature can speak (is not muted).
bool CurrentCreatureAbilities::can_speak(CreaturePtr creature, const bool add_message_if_player_and_cannot_speak) const
{
  bool creature_can_speak = creature && can_act(creature) && (creature->has_status(StatusIdentifiers::STATUS_ID_MUTE) == false);

  if (add_message_if_player_and_cannot_speak && !creature_can_speak && creature && creature->get_is_player())
  {
    add_ability_message_for_sid(creature, StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_MUTED);
  }

  return creature_can_speak;
}

// Check to see if the creature can focus (is not enraged).
// Creatures without focus can't cast spells, read, or use evocables.
bool CurrentCreatureAbilities::can_focus(CreaturePtr creature, const bool add_message_if_player_and_cannot_focus) const
{
  bool creature_can_focus = creature && can_act(creature) && (creature->has_status(StatusIdentifiers::STATUS_ID_RAGE) == false);

  if (add_message_if_player_and_cannot_focus && !creature_can_focus && creature && creature->get_is_player())
  {
    add_ability_message_for_sid(creature, StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_RAGE);
  }

  return creature_can_focus;
}

// Check to see if the creature can see (has not been blinded).
bool CurrentCreatureAbilities::can_see(CreaturePtr creature, const bool add_message_if_player_and_cannot_see) const
{
  bool creature_can_see = creature && (creature->has_status(StatusIdentifiers::STATUS_ID_BLINDED) == false);

  if (add_message_if_player_and_cannot_see && !creature_can_see && creature && creature->get_is_player())
  {
    add_ability_message_for_sid(creature, StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_BLINDED);
  }

  return creature_can_see;
}

bool CurrentCreatureAbilities::can_hear(CreaturePtr creature, const bool /*add_message_if_player_and_cannot_hear*/) const
{
  bool creature_can_hear = creature != nullptr;

  return creature_can_hear;
}

// Check to see if the creature can move (isn't spellbound, overburdened, etc)
bool CurrentCreatureAbilities::can_move(CreaturePtr creature, const bool add_message_if_player_and_cannot_move) const
{
  CarryingCapacityCalculator ccc;

  bool creature_can_move = creature 
                        // Is the creature paralyzed?
                        && can_act(creature) 
                        // Is the creature spellbound?
                        && (creature->has_status(StatusIdentifiers::STATUS_ID_SPELLBOUND) == false) 
                        // Is the creature overburdened by the weight they're carrying?
                        && !(creature->get_weight_carried() >= ccc.calculate_overburdened_weight(creature))
                        // Is the creature using a mobile decision strategy?
                        && creature->get_decision_strategy()->can_move();

  if (add_message_if_player_and_cannot_move && !creature_can_move && creature && creature->get_is_player())
  {
    add_ability_message_for_sid(creature, StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_IMMOBILE);
  }

  return creature_can_move;
}

// Check to see if the creature can act (is not paralyzed)
bool CurrentCreatureAbilities::can_act(CreaturePtr creature, const bool add_message_if_player_and_cannot_speak) const
{
  bool creature_can_act = creature && (creature->has_status(StatusIdentifiers::STATUS_ID_PARALYSIS) == false);

  if (add_message_if_player_and_cannot_speak && !creature_can_act && creature && creature->get_is_player())
  {
    add_ability_message_for_sid(creature, StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_PARALYZED);
  }

  return creature_can_act;
}

// Can the creature read? (has Literacy)
bool CurrentCreatureAbilities::can_read(CreaturePtr creature, const bool add_message_if_player_and_cannot_read) const
{
  bool creature_can_read = creature && (creature->get_skills().get_value(SkillType::SKILL_GENERAL_LITERACY) > 0);

  if (add_message_if_player_and_cannot_read && !creature_can_read && creature && creature->get_is_player())
  {
    add_ability_message_for_sid(creature, StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_ILLITERATE);
  }

  return creature_can_read;
}

// Check to see if the creature can select their movement direction -
// false if the creature is stunned.
bool CurrentCreatureAbilities::can_select_movement_direction(CreaturePtr creature, const bool add_message_if_player_and_stunned) const
{
  bool creature_can_select = creature && (creature->has_status(StatusIdentifiers::STATUS_ID_STUNNED) == false);

  if (add_message_if_player_and_stunned && !creature_can_select && creature && creature->get_is_player())
  {
    add_ability_message_for_sid(creature, StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_STUNNED);
  }

  return creature_can_select;
}

void CurrentCreatureAbilities::add_ability_message_for_sid(CreaturePtr creature, const string& status_ability_message_sid) const
{
  IMessageManager& manager = MMF::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(status_ability_message_sid));
  manager.send();
}

bool CurrentCreatureAbilities::can_prise(CreaturePtr creature) const
{
  bool prise = false;

  if (creature != nullptr)
  {
    ItemPtr item = creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);
    prise = (item && item->get_additional_property(ItemProperties::ITEM_PROPERTIES_PRISE) == std::to_string(true));
  }

  return prise;
}

#ifdef UNIT_TESTS
#include "unit_tests/CurrentCreatureAbilities_test.cpp"
#endif