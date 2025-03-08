#include "ActionTextKeys.hpp"
#include "WaterBreathingStatusEffect.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusTypes.hpp"
#include "WaterBreathingCalculator.hpp"

using namespace std;

WaterBreathingStatusEffect::WaterBreathingStatusEffect()
{
  status_calc = std::make_shared<WaterBreathingCalculator>();
}

bool WaterBreathingStatusEffect::is_negative() const
{
  return false;
}

string WaterBreathingStatusEffect::get_player_application_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_WATER_BREATHING);
  return message;
}

string WaterBreathingStatusEffect::get_npc_application_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_water_breathing_message(creature);
  return message;
}

string WaterBreathingStatusEffect::get_player_finalize_message() const
{
  return get_player_undo_message();
}

string WaterBreathingStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_WATER_BREATHING_CURED);
  return message;
}

string WaterBreathingStatusEffect::get_npc_undo_message(CreaturePtr creature) const
{
  string message = StatusAilmentTextKeys::get_npc_undo_water_breathing_message(creature);

  return message;
}

string WaterBreathingStatusEffect::get_status_identifier() const
{
  return StatusIdentifiers::STATUS_ID_WATER_BREATHING;
}

void WaterBreathingStatusEffect::after_finalize(std::shared_ptr<Creature> creature) const
{
  if (creature != nullptr)
  {
    creature->get_movement_accumulation_ref().reset_minutes();
  }
}