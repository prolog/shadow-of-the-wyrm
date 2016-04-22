#include "CombatManager.hpp"
#include "MountainClimbingMovementAccumulationChecker.hpp"
#include "RNG.hpp"

// Check to see if the creature falls.  Falling deals lump sum damage, influenced
// by how many turns past exhaustion have been spent mountain climbing.
void MountainClimbingMovementAccumulationChecker::check(CreaturePtr creature)
{
  if (creature)
  {
    int mountaineering_skill_value = sm.get_skill_value(creature, SkillType::SKILL_GENERAL_MOUNTAINEERING);
    ulonglong max_climbing_time = static_cast<ulonglong>(mcc.calculate_max_mountain_climbing_time(mountaineering_skill_value, creature->has_status(StatusIdentifiers::STATUS_ID_INCORPOREAL)));
    MovementAccumulation& movement_accumulation = creature->get_movement_accumulation_ref();
    ulonglong time_on_mt = movement_accumulation.get_minutes_on_tile_type_given_movement();

    if (time_on_mt > max_climbing_time)
    {
      mountaineering.process(creature, nullptr);
    }
    else
    {
      if (RNG::percent_chance(10))
      {
        sm.check_skill(creature, SkillType::SKILL_GENERAL_MOUNTAINEERING);
      }
    }
  }
}
