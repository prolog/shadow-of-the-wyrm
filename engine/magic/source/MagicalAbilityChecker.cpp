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

bool MagicalAbilityChecker::has_sufficient_power(CreaturePtr creature, const Spell& spell) const
{
  if (creature)
  {
    uint ap_cost = spell.get_ap_cost();
    int creature_ap = creature->get_arcana_points().get_current();

    if (creature_ap > 0)
    {
      uint creature_uap = static_cast<uint>(creature_ap);

      if (creature_uap >= ap_cost) return true;
    }
  }

  return false;
}

#ifdef UNIT_TESTS
#include "unit_tests/MagicalAbilityChecker_test.cpp"
#endif
