#include "BeastmasteryCalculator.hpp"

const int BeastmasteryCalculator::MAX_PCT_CHANCE_TAME = 90;

int BeastmasteryCalculator::calculate_pct_chance_tame(CreaturePtr taming_creature)
{
  int taming_pct = 0;

  if (taming_creature != nullptr)
  {
    taming_pct = taming_creature->get_skills().get_value(SkillType::SKILL_GENERAL_BEASTMASTERY) - 10;

    taming_pct = std::max<int>(taming_pct, 0);
    taming_pct = std::min<int>(taming_pct, MAX_PCT_CHANCE_TAME);
  }

  return taming_pct;
}

#ifdef UNIT_TESTS
#include "unit_tests/BeastmasteryCalculator_test.cpp"
#endif
