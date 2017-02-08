#include "CreateItemCalculator.hpp"

const int CreateItemCalculator::PRIMARY_SKILL_DIVISOR = 7;
const int CreateItemCalculator::CRAFTING_SKILL_DIVISOR = 15;

int CreateItemCalculator::calc_potential_improvement_points(CreaturePtr creature, const SkillType create_skill)
{
  int improve_points = 0;

  if (creature != nullptr)
  {
    Skills& skills = creature->get_skills();

    improve_points += (skills.get_value_incr_marks(create_skill) / PRIMARY_SKILL_DIVISOR);
    improve_points += (skills.get_value_incr_marks(SkillType::SKILL_GENERAL_CRAFTING) / CRAFTING_SKILL_DIVISOR);
  }

  return improve_points;
}

#ifdef UNIT_TESTS
#include "unit_tests/CreateItemCalculator_test.cpp"
#endif


