#include "PrimordialCalculator.hpp"

const int PrimordialCalculator::SKILL_CASTINGS_DIVISOR = 10;

int PrimordialCalculator::get_max_skill_castings(CreaturePtr creature)
{
  int castings = 0;

  if (creature != nullptr)
  {
    int pri_val = creature->get_skills().get_value(SkillType::SKILL_MAGIC_PRIMORDIAL);

    if (pri_val > 0)
    {
      castings = std::max<int>(1, pri_val / SKILL_CASTINGS_DIVISOR);
    }
  }

  return castings;
}

#ifdef UNIT_TESTS
#include "unit_tests/PrimordialCalculator_test.cpp"
#endif
