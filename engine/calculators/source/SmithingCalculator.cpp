#include "SmithingCalculator.hpp"

using namespace std;

vector<int> SmithingCalculator::calculate_pct_chances_extra_point(CreaturePtr creature, const SkillType primary_crafting_skill)
{
  vector<int> pct_chances;

  if (creature != nullptr)
  {
    Skills& skills = creature->get_skills();
    int primary_value = skills.get_value(primary_crafting_skill);
    int crafting_value = skills.get_value(SkillType::SKILL_GENERAL_CRAFTING);

    pct_chances = {primary_value, (crafting_value / 3)};
  }

  return pct_chances;
}

#ifdef UNIT_TESTS
#include "unit_tests/SmithingCalculator_test.cpp"
#endif

