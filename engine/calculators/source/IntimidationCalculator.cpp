#include "IntimidationCalculator.hpp"

const int IntimidationCalculator::MAX_PCT_CHANCE_INTIMIDATION = 85;
const int IntimidationCalculator::INTIMIDATION_DIVISOR = 3;
const int IntimidationCalculator::CHARISMA_DIVISOR = 4;

int IntimidationCalculator::calculate_pct_chance_intimidated(CreaturePtr attacking_creature, CreaturePtr attacked_creature)
{
  int pct_chance = 0;

  if (attacking_creature != nullptr && attacked_creature != nullptr)
  {
    int attack_intim = attacking_creature->get_skills().get_value(SkillType::SKILL_GENERAL_INTIMIDATION);
    int attack_cha = attacking_creature->get_charisma().get_current();

    int attacked_intim = attacked_creature->get_skills().get_value(SkillType::SKILL_GENERAL_INTIMIDATION);
    int attacked_cha = attacked_creature->get_charisma().get_current();

    if (attacked_intim > 0)
    {
      int attack = (attack_intim / INTIMIDATION_DIVISOR) + (attack_cha / CHARISMA_DIVISOR);
      int attacked = (attacked_intim / INTIMIDATION_DIVISOR) + (attacked_cha / CHARISMA_DIVISOR);

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
