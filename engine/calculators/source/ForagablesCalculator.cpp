#include "ForagablesCalculator.hpp"

int ForagablesCalculator::calculate_pct_chance_foragables(CreaturePtr creature)
{
  int pct_chance = 0;

  if (creature != nullptr)
  {
    pct_chance = creature->get_skills().get_value_incr_marks(SkillType::SKILL_GENERAL_FORAGING);
  }

  return pct_chance;
}

int ForagablesCalculator::calculate_pct_chance_herbs(CreaturePtr creature)
{
  int pct_chance = 0;

  if (creature != nullptr)
  {
    pct_chance = creature->get_skills().get_value_incr_marks(SkillType::SKILL_GENERAL_HERBALISM) / 3;
  }

  return pct_chance;
}

#ifdef UNIT_TESTS
#include "unit_tests/ForagablesCalculator_test.cpp"
#endif