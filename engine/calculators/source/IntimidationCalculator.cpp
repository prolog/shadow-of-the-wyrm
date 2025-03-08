#include "IntimidationCalculator.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "RaceManager.hpp"

const int IntimidationCalculator::MAX_PCT_CHANCE_INTIMIDATION = 85;
const int IntimidationCalculator::INTIMIDATION_DIVISOR = 3;
const int IntimidationCalculator::CHARISMA_DIVISOR = 4;
const int IntimidationCalculator::LEVEL_DIVISOR = 2;

int IntimidationCalculator::calculate_pct_chance_intimidated(CreaturePtr attacking_creature, CreaturePtr attacked_creature)
{
  int pct_chance = 0;
  CurrentCreatureAbilities cca;

  if (attacking_creature != nullptr && attacked_creature != nullptr && cca.can_act(attacked_creature))
  {
    RaceManager rm;
    Race* race = rm.get_race(attacked_creature->get_race_id());

    if (race != nullptr && race->get_mindless())
    {
      return 0;
    }

    bool attacking_raging = attacking_creature->has_status(StatusIdentifiers::STATUS_ID_RAGE);

    if (attacking_raging)
    {
      return 0;
    }

    int attack_intim = attacking_creature->get_skills().get_value(SkillType::SKILL_GENERAL_INTIMIDATION);
    int attack_cha = attacking_creature->get_charisma().get_current();
    int attack_level = attacking_creature->get_level().get_current();

    int attacked_intim = attacked_creature->get_skills().get_value(SkillType::SKILL_GENERAL_INTIMIDATION);
    int attacked_cha = attacked_creature->get_charisma().get_current();
    int attacked_level = attacked_creature->get_level().get_current();

    // Check to see if the attacked creature has intimidation - this can cause
    // the attacker to pull back in fear.
    if (attacked_intim > 0)
    {
      int attack = (attack_intim / INTIMIDATION_DIVISOR) + (attack_cha / CHARISMA_DIVISOR) + (attack_level / LEVEL_DIVISOR);
      int attacked = (attacked_intim / INTIMIDATION_DIVISOR) + (attacked_cha / CHARISMA_DIVISOR) + (attacked_level / LEVEL_DIVISOR);

      pct_chance = attacked - attack;
      pct_chance = std::max(0, pct_chance);
      pct_chance = std::min(MAX_PCT_CHANCE_INTIMIDATION, pct_chance);
    }
  }

  return pct_chance;
}

#ifdef UNIT_TESTS
#include "unit_tests/IntimidationCalculator_test.cpp"
#endif
