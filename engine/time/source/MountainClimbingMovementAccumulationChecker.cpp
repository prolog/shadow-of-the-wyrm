#include "CombatManager.hpp"
#include "MountainClimbingMovementAccumulationChecker.hpp"

using std::string;

// Check to see if the creature falls.  Falling deals lump sum damage, influenced
// by how many turns past exhaustion have been spent mountain climbing.
void MountainClimbingMovementAccumulationChecker::check(CreaturePtr creature)
{
  if (creature)
  {
    int mountaineering_skill_value = sm.get_skill_value(creature, SKILL_GENERAL_MOUNTAINEERING);
    int max_climbing_time = mcc.calculate_max_mountain_climbing_time(mountaineering_skill_value);
    MovementAccumulation& movement_accumulation = creature->get_movement_accumulation_ref();
    int time_on_mt = movement_accumulation.get_minutes_on_tile_type_given_movement();

    if (time_on_mt > max_climbing_time)
    {
      check_for_fall(creature, mountaineering_skill_value);
    }
  }
}

void MountainClimbingMovementAccumulationChecker::check_for_fall(CreaturePtr creature, const int mountaineering_skill_value)
{
  if (creature)
  {
    if (mcc.generate_does_fall_from_exhaustion(mountaineering_skill_value))
    {
      string fall_message_sid;
      
      if (creature->get_is_player())
      {
        fall_message_sid = ActionTextKeys::ACTION_PLAYER_FALL_FROM_MOUNTAIN;
      }
      
      CombatManager cm;
      CreaturePtr no_attacker;
      cm.deal_damage(no_attacker, creature, mcc.generate_falling_damage(), fall_message_sid);

      // Reset counter, since we're no longer "on" the mt.
      creature->get_movement_accumulation_ref().set_minutes_on_tile_type_given_movement(0); 
    }
  }
}
