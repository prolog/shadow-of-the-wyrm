#include "SpellBonusUpdater.hpp"

// Increment the current counter.  If this equals the base afterwards,
// reset the current, increment the base, and return true.
//
// Otherwise, return false, to indicate that the statistic's base value
// was not updated.
bool SpellBonusUpdater::add_successful_casting(IndividualSpellKnowledge& isk) const
{
  bool incremented_base = false;

  Statistic spell_bonus = isk.get_bonus();

  int cur  = spell_bonus.get_current() + 1;
  int base = spell_bonus.get_base(); 

  if (cur >= base)
  {
    spell_bonus.set_current(0);
    spell_bonus.set_base(base + 1);

    incremented_base = true;
  }
  else
  {
    spell_bonus.set_current(cur);
  }

  isk.set_bonus(spell_bonus);

  return incremented_base;
}

#ifdef UNIT_TESTS
#include "unit_tests/SpellBonusUpdater_test.cpp"
#endif
