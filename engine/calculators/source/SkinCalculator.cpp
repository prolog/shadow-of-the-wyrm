#include "SkinCalculator.hpp"

// The chance to create a skin is min(35 + skinning skill, 100)
int SkinCalculator::calculate_chance_successful_skin(CreaturePtr creature)
{
  int pct_chance = 0;

  if (creature)
  {
    int skin_value = creature->get_skills().get_value(SKILL_GENERAL_SKINNING);
    pct_chance = std::min(35 + skin_value, 100);
  }

  return pct_chance;
}

#ifdef UNIT_TESTS
#include "unit_tests/SkinCalculator_test.cpp"
#endif

