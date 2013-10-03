#include "MagicToHitCalculator.hpp"
#include "SkillManager.hpp"

MagicToHitCalculator::MagicToHitCalculator()
: ToHitCalculator(ATTACK_TYPE_MAGICAL)
{
}

int MagicToHitCalculator::calculate(CreaturePtr creature)
{
  int to_hit = 0;

  if (creature)
  {
    SkillManager sm;

    int magic_bonus  = sm.get_skill_value(creature, SKILL_GENERAL_MAGIC) / NWP_SKILL_BONUS_DIVISOR;
    int intelligence = creature->get_intelligence().get_current();
    
    to_hit += magic_bonus;
    to_hit += (intelligence - 10) / 3;
  }

  return to_hit;
}

#ifdef UNIT_TESTS
#include "unit_tests/MagicToHitCalculator_test.cpp"
#endif
