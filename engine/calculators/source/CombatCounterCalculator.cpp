#include "CombatCounterCalculator.hpp"

const int CombatCounterCalculator::COMBAT_SKILL_DIVISOR = 10;
const int CombatCounterCalculator::DEXTERITY_DIVISOR = 5;

int CombatCounterCalculator::calc_pct_chance_counter_strike(CreaturePtr creature) const
{
  int pct_counter = 0;

  if (creature != nullptr && !creature->is_dead())
  {
    int combat_val = creature->get_skills().get_value(SkillType::SKILL_GENERAL_COMBAT) / COMBAT_SKILL_DIVISOR;
    pct_counter += combat_val;

    // If the creature meets the minimum combat skill threshold for
    // counter-attacking, add the dexterity bonus.
    if (combat_val > 0)
    {
      int dex_val = (creature->get_dexterity().get_current() / DEXTERITY_DIVISOR);
      pct_counter += dex_val;
    }
  }

  return pct_counter;
}

#ifdef UNIT_TESTS
#include "unit_tests/CombatCounterCalculator_test.cpp"
#endif

