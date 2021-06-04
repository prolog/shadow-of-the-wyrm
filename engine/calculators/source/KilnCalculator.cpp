#include "KilnCalculator.hpp"

const int KilnCalculator::ENCHANTS_CRAFTING_DIVISOR = 10;

int KilnCalculator::calc_pct_chance_brand() const
{
  return 0;
}

int KilnCalculator::calc_min_free_enchants(CreaturePtr creature) const
{
  int enchants = 0;

  if (creature != nullptr)
  {
    int skill_val = std::min<int>(ENCHANTS_CRAFTING_DIVISOR, creature->get_skills().get_value(SkillType::SKILL_GENERAL_CRAFTING));
    enchants = skill_val / ENCHANTS_CRAFTING_DIVISOR;
  }

  return enchants;
}

int KilnCalculator::calc_max_free_enchants(CreaturePtr creature) const
{
  int enchants = 0;

  if (creature != nullptr)
  {
    enchants = creature->get_skills().get_value(SkillType::SKILL_GENERAL_CRAFTING) / ENCHANTS_CRAFTING_DIVISOR;
  }

  return enchants;
}

#ifdef UNIT_TESTS
#include "unit_tests/KilnCalculator_test.cpp"
#endif
