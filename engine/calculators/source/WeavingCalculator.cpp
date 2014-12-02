#include "WeavingCalculator.hpp"

int WeavingCalculator::calculate_min_enchant_points(CreaturePtr creature)
{
  int min_points = 0;

  if (creature)
  {
    int weaving_skill = creature->get_skills().get_value(SKILL_GENERAL_WEAVING);
    min_points = (weaving_skill / 20);
  }

  return min_points;
}

int WeavingCalculator::calculate_max_enchant_points(CreaturePtr creature)
{
  int max_points = 0;

  if (creature)
  {
    int weaving_skill = creature->get_skills().get_value(SKILL_GENERAL_WEAVING);
    max_points = (weaving_skill / 10);
  }

  return max_points;
}

#ifdef UNIT_TESTS
#include "unit_tests/WeavingCalculator_test.cpp"
#endif
