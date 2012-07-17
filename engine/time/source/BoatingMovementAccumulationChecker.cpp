#include "BoatingMovementAccumulationChecker.hpp"

void BoatingMovementAccumulationChecker::check(CreaturePtr creature)
{
  if (creature)
  {
    sm.check_skill(creature, SKILL_GENERAL_BOATING);
  }
}
