#include "CorpseCalculator.hpp"

// The chance to create a skin is min(35 + (skinning skill / 2) + (crafting skill / 4), 100)
int CorpseCalculator::calculate_chance_successful_skin(CreaturePtr creature)
{
  int pct_chance = 0;

  if (creature)
  {
    Skills& skills = creature->get_skills();
    int skin_value = skills.get_value(SkillType::SKILL_GENERAL_SKINNING);
    int craft_value = skills.get_value(SkillType::SKILL_GENERAL_CRAFTING);

    pct_chance = std::min(35 + (skin_value / 2) + (craft_value / 4), 100);
  }

  return pct_chance;
}

// The chance for a creature to carry over a particular resistance is
// 25 + (skinning skill / 3)
int CorpseCalculator::calculate_chance_resistance(CreaturePtr creature)
{
  int pct_chance = 25;

  if (creature != nullptr)
  {
    pct_chance += static_cast<int>(creature->get_skills().get_value(SkillType::SKILL_GENERAL_SKINNING) / 3);
  }

  return pct_chance;
}

// The chance of a corpse is 7% + (hunting / 2) + (foraging / 3).
// The maximum chance is 80%.
int CorpseCalculator::calculate_chance_corpse(CreaturePtr deathblow_creature)
{
  int pct_chance = 0;

  if (deathblow_creature)
  {
    Skills& skills = deathblow_creature->get_skills();

    int forage_value = skills.get_value_incr_marks(SkillType::SKILL_GENERAL_FORAGING);
    int hunt_value = skills.get_value_incr_marks(SkillType::SKILL_GENERAL_HUNTING);

    pct_chance = std::min(7 + (forage_value / 3) + (hunt_value / 2), 80);
  }

  return pct_chance;
}

#ifdef UNIT_TESTS
#include "unit_tests/CorpseCalculator_test.cpp"
#endif

