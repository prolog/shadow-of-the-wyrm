#include "MagicalAbilityChecker.hpp"

// Check to see whether a creature has any magical knowledge by counting
// the number of spells known.
bool MagicalAbilityChecker::has_magical_knowledge(CreaturePtr creature) const
{
  bool has_knowledge = false;

  if (creature)
  {
    SpellKnowledge& sk = creature->get_spell_knowledge_ref();
    has_knowledge = (sk.count_spells_known() > 0);
  }

  return has_knowledge;
}

#ifdef UNIT_TESTS
#include "unit_tests/MagicalAbilityChecker_test.cpp"
#endif
