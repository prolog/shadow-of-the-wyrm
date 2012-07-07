#include "CombatManager.hpp"
#include "StringConstants.hpp"
#include "SwimmingCalculator.hpp"
#include "SwimmingMovementAccumulationChecker.hpp"

using std::string;

// Check for damage due to swimming past the point of exhaustion.
void SwimmingMovementAccumulationChecker::check(CreaturePtr creature)
{
  if (creature)
  {
    int max_swimming_time = sc.calculate_maximum_swimming_time(sm.get_skill_value(creature, SKILL_GENERAL_SWIMMING));
    MovementAccumulation& movement_accumulation = creature->get_movement_accumulation_ref();
    int time_in_water = movement_accumulation.get_minutes_on_super_type_given_movement();

    if (time_in_water > max_swimming_time)
    {
      drown(creature);
    }
  }
}

// "Drown" the creature by applying swimming damage.
// If the creature is the player, display a UI message.
void SwimmingMovementAccumulationChecker::drown(CreaturePtr creature)
{
  if (creature)
  {
    string drowning_message_sid;
    
    if (creature->get_is_player())
    {
      drowning_message_sid = ActionTextKeys::ACTION_PLAYER_DROWNING;
    }
    
    CombatManager cm;
    CreaturePtr no_attacker;
    cm.deal_damage(no_attacker, creature, sc.calculate_swimming_damage(creature), drowning_message_sid);    
  }
}
