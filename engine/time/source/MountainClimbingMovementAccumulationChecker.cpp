#include "CombatManager.hpp"
#include "MountainClimbingMovementAccumulationChecker.hpp"

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
      mountaineering.check_for_fall(creature);
    }
    else
    {
      sm.check_skill(creature, SKILL_GENERAL_MOUNTAINEERING);
    }
  }
}
