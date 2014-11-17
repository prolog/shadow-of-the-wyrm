#include "CorpseCalculator.hpp"

// The chance to create a skin is min(35 + skinning skill, 100)
int CorpseCalculator::calculate_chance_successful_skin(CreaturePtr creature)
{
  int pct_chance = 0;

  if (creature)
  {
    int skin_value = creature->get_skills().get_value(SKILL_GENERAL_SKINNING);
    pct_chance = std::min(35 + skin_value, 100);
  }

  return pct_chance;
}

// The chance of a corpse is 15% + (foraging skill / 4)
int CorpseCalculator::calculate_chance_corpse(CreaturePtr deathblow_creature)
{
  int pct_chance = 0;

  if (deathblow_creature)
  {
    int forage_value = deathblow_creature->get_skills().get_value(SKILL_GENERAL_FORAGING);
    pct_chance = std::min(15 + (forage_value / 4), 100);
  }

  return pct_chance;
}

#ifdef UNIT_TESTS
#include "unit_tests/CorpseCalculator_test.cpp"
#endif

