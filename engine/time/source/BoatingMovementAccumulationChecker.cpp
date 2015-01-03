#include "BoatingMovementAccumulationChecker.hpp"
#include "RNG.hpp"

void BoatingMovementAccumulationChecker::check(CreaturePtr creature)
{
  if (creature)
  {
    if (RNG::percent_chance(10))
    {
      sm.check_skill(creature, SkillType::SKILL_GENERAL_BOATING);
    }
  }
}
