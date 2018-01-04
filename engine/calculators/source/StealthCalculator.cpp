#include "StealthCalculator.hpp"

// Hidden creatures always sneak attack.
//
// When not hidden, there is a small (Stealth/10 %) chance of a creature 
// getting in a sneak attack, if the creature has any Stealth skill.  The 
// minimum value is always 1%.
int StealthCalculator::calculate_pct_chance_sneak_attack(CreaturePtr creature) const
{
  int pct_chance = 0;

  if (creature != nullptr)
  {
    if (creature->has_status(StatusIdentifiers::STATUS_ID_HIDE))
    {
      pct_chance = 100;
    }
    else
    {
      int stealth_val = creature->get_skills().get_value(SkillType::SKILL_GENERAL_STEALTH);

      if (stealth_val > 0)
      {
        pct_chance = std::max<int>(stealth_val / 10, 1);
      }
    }
  }

  return pct_chance;
}

#ifdef UNIT_TESTS
#include "unit_tests/StealthCalculator_test.cpp"
#endif

