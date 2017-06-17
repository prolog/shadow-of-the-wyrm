#include "ScythingCalculator.hpp"

// For each creature that has been hit so far, the chance of the attack
// continuing is reduced slightly.
const int ScythingCalculator::SCYTHING_ATTACK_MULTIPLIER = 10;

// The chance that scything continues is based off the creature's skill in a
// particular skill (typically, the weapon skill for the weapon that is
// scything).  This is reduced if the current attack missed, and also based
// on the total number of creatures that have been hit by the scything attack
// so far.
int ScythingCalculator::calc_pct_chance_scything_continues(CreaturePtr creature, const SkillType st, const int total_attacks)
{
  int chance_scy = 0;

  if (creature != nullptr)
  {
    int val = creature->get_skills().get_value(st);
    chance_scy = val - (total_attacks * SCYTHING_ATTACK_MULTIPLIER);
    chance_scy = std::max<int>(0, chance_scy);
  }

  return chance_scy;
}

#ifdef UNIT_TESTS
#include "unit_tests/ScythingCalculator_test.cpp"
#endif

