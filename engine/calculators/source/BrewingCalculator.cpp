#include "BrewingCalculator.hpp"

const int BrewingCalculator::ADDITIONAL_POTION_BREWING_DIVISOR = 4;

int BrewingCalculator::calc_pct_chance_additional_potion(CreaturePtr creature) const
{
  int pct_chance = 0;

  if (creature != nullptr)
  {
    int brewing_val = creature->get_skills().get_value(SkillType::SKILL_GENERAL_BREWING);

    if (brewing_val == 100)
    {
      pct_chance = 100;
    }
    else
    {
      pct_chance = brewing_val / ADDITIONAL_POTION_BREWING_DIVISOR;
    }
  }

  return pct_chance;
}

#ifdef UNIT_TESTS
#include "unit_tests/BrewingCalculator_test.cpp"
#endif
