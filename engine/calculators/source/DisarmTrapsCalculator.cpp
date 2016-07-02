#include "DisarmTrapsCalculator.hpp"
#include "RNG.hpp"

const float DisarmTrapsCalculator::DISARM_TRAPS_SKILL_MULTIPLIER = 0.9f;
const float DisarmTrapsCalculator::DISMANTLE_TRAPS_SKILL_MULTIPLIER = 0.8f;

DisarmTrapsOutcome DisarmTrapsCalculator::calculate_disarm_traps_outcome(CreaturePtr creature, const bool has_component_items)
{
  DisarmTrapsOutcome dto = DisarmTrapsOutcome::DISARM_TRAPS_FAIL;

  // If a disarm traps attempt would ordinarily end in failure, there's
  // a 50% chance of triggering the trap.
  if (RNG::percent_chance(50))
  {
    dto = DisarmTrapsOutcome::DISARM_TRAPS_TRIGGER;
  }

  if (creature != nullptr)
  {
    // There is a (.9 * Disarm Traps)% chance of disarming a trap.
    int val = creature->get_skills().get_value(SkillType::SKILL_GENERAL_DISARM_TRAPS);
    int disarm_chance = static_cast<int>(val * DISARM_TRAPS_SKILL_MULTIPLIER);

    if (has_component_items && RNG::percent_chance(disarm_chance))
    {
      dto = DisarmTrapsOutcome::DISARM_TRAPS_DISARM;

      // If a trap is disarmed, there is a (.8 * Disarm Traps)% chance of
      // dismantling the trap and getting something useful.
      int dismantle_chance = static_cast<int>(val * DISMANTLE_TRAPS_SKILL_MULTIPLIER);

      if (RNG::percent_chance(dismantle_chance))
      {
        dto = DisarmTrapsOutcome::DISARM_TRAPS_DISMANTLE;
      }
    }
  }

  return dto;
}

