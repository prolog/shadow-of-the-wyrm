#include "BeastmasteryCalculator.hpp"

const int BeastmasteryCalculator::MAX_PCT_CHANCE_TAME = 80;

int BeastmasteryCalculator::calculate_pct_chance_tame(CreaturePtr taming_creature, CreaturePtr tamed_creature)
{
  int taming_pct = 0;

  if (taming_creature != nullptr && tamed_creature != nullptr)
  {
    taming_pct = taming_creature->get_skills().get_value(SkillType::SKILL_GENERAL_BEASTMASTERY) - 10;
    int level_diff = taming_creature->get_level().get_current() - tamed_creature->get_level().get_current();

    taming_pct += level_diff;

    taming_pct = std::max<int>(taming_pct, 0);
    taming_pct = std::min<int>(taming_pct, MAX_PCT_CHANCE_TAME);
  }

  return taming_pct;
}

double BeastmasteryCalculator::calculate_exp_proportion(CreaturePtr taming_creature)
{
  double exp = 0.0;

  if (taming_creature != nullptr)
  {
    exp = taming_creature->get_skills().get_value(SkillType::SKILL_GENERAL_BEASTMASTERY) / 100.0;
  }

  return exp;
}

#ifdef UNIT_TESTS
#include "unit_tests/BeastmasteryCalculator_test.cpp"
#endif
