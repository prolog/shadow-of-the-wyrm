#include "BoatingMovementAccumulationChecker.hpp"
#include "RNG.hpp"

void BoatingMovementAccumulationChecker::check(CreaturePtr creature)
{
  if (creature)
  {
    if (RNG::x_in_y_chance(1, 500))
    {
      sm.check_skill(creature, SkillType::SKILL_GENERAL_BOATING);
    }
  }
}
