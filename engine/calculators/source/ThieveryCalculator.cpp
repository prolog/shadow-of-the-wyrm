#include "ThieveryCalculator.hpp"
#include "CalcUtils.hpp"
#include "CurrentCreatureAbilities.hpp"

// The chance to steal is:
//
// Stealing creature's Thievery score +
// Stealing creature's Dexterity score -
// Target creature's Agility score
//
// If the Target creature is blind, multiply by 4.
int ThieveryCalculator::calculate_pct_chance_steal(CreaturePtr stealing_creature, CreaturePtr steal_creature)
{
  int steal_chance = 0;

  if (stealing_creature != nullptr && steal_creature != nullptr)
  {
    int thievery = stealing_creature->get_skills().get_value(SkillType::SKILL_GENERAL_THIEVERY);
    int stealing_dex = stealing_creature->get_dexterity().get_current();
    int target_agi = steal_creature->get_agility().get_current();

    steal_chance = thievery + stealing_dex - target_agi;

    CurrentCreatureAbilities cca;

    if (!cca.can_see(steal_creature))
    {
      steal_chance *= 4;
    }
  }

  return CalcUtils::pct_val(steal_chance);
}

#ifdef UNIT_TESTS
#include "unit_tests/ThieveryCalculator_test.cpp"
#endif

