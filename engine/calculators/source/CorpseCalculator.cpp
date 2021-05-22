#include "CorpseCalculator.hpp"

const int CorpseCalculator::BASE_CHANCE_PRIMORDIAL_ESSENCE = 5;
const int CorpseCalculator::PRIMORDIAL_ESSENCE_SKILL_DIVISOR = 5;

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

int CorpseCalculator::calculate_chance_primordial_essence(CreaturePtr attacking_creature, CreaturePtr deathblow_creature)
{
  int pct_chance = 0;

  if (deathblow_creature != nullptr)
  {
    Damage damage = deathblow_creature->get_base_damage();

    if (damage.get_damage_type() == DamageType::DAMAGE_TYPE_SHADOW)
    {
      pct_chance = BASE_CHANCE_PRIMORDIAL_ESSENCE;

      if (attacking_creature != nullptr)
      {
        int skill_value = std::max<int>(attacking_creature->get_skills().get_value(SkillType::SKILL_MAGIC_PRIMORDIAL),
          attacking_creature->get_skills().get_value(SkillType::SKILL_GENERAL_DUNGEONEERING));

        pct_chance += (skill_value / PRIMORDIAL_ESSENCE_SKILL_DIVISOR);
      }
    }
  }

  return pct_chance;
}

#ifdef UNIT_TESTS
#include "unit_tests/CorpseCalculator_test.cpp"
#endif

