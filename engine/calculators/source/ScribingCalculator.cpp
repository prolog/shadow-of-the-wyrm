#include "ScribingCalculator.hpp"

const int ScribingCalculator::MAX_CASTINGS_PER_SCROLL = 7;
const int ScribingCalculator::MIN_CASTINGS_PER_SCROLL = 2;
const int ScribingCalculator::SCRIBING_DIVISOR = 20;

int ScribingCalculator::calc_castings_per_scroll(CreaturePtr creature)
{
  int castings = MAX_CASTINGS_PER_SCROLL;

  if (creature != nullptr)
  {
    int scribing_val = creature->get_skills().get_value(SkillType::SKILL_GENERAL_SCRIBING);
    castings -= (scribing_val / SCRIBING_DIVISOR);
    castings = std::max<int>(castings, MIN_CASTINGS_PER_SCROLL);
  }

  return castings;
}

#ifdef UNIT_TESTS
#include "unit_tests/ScribingCalculator_test.cpp"
#endif
