#include "WeavingCalculator.hpp"

int WeavingCalculator::calculate_min_enchant_points(CreaturePtr creature)
{
  int min_points = 0;

  if (creature)
  {
    Skills& skills = creature->get_skills();
    int weaving_skill = skills.get_value(SkillType::SKILL_GENERAL_WEAVING);
    int crafting_skill = skills.get_value(SkillType::SKILL_GENERAL_CRAFTING);

    min_points = (weaving_skill / 25) + (crafting_skill / 25);
  }

  return min_points;
}

int WeavingCalculator::calculate_max_enchant_points(CreaturePtr creature)
{
  int max_points = 0;

  if (creature)
  {
    Skills& skills = creature->get_skills();
    int weaving_skill = skills.get_value(SkillType::SKILL_GENERAL_WEAVING);
    int crafting_skill = skills.get_value(SkillType::SKILL_GENERAL_CRAFTING);

    max_points = (weaving_skill / 10) + (crafting_skill / 20);
  }

  return max_points;
}

#ifdef UNIT_TESTS
#include "unit_tests/WeavingCalculator_test.cpp"
#endif
