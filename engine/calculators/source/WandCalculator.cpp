#include "WandCalculator.hpp"

const int WandCalculator::DAMAGE_BONUS_STAT_DIVISOR = 15;
const int WandCalculator::DAMAGE_BONUS_SKILL_DIVISOR = 5;
const int WandCalculator::FREE_CHARGE_SKILL_DIVISOR = 10;

// The evoker of a wand gets a damage bonus influenced largely by Wandcraft,
// but also to a lesser extent by Willpower.
int WandCalculator::calc_damage_bonus(CreaturePtr creature)
{
  int dmg_bonus = 0;

  if (creature != nullptr)
  {
    int wand_val = creature->get_skills().get_value(SkillType::SKILL_GENERAL_WANDCRAFT);
    int willpower = creature->get_willpower().get_current();

    dmg_bonus = wand_val / DAMAGE_BONUS_SKILL_DIVISOR;
    dmg_bonus += willpower / DAMAGE_BONUS_STAT_DIVISOR;
  }

  return dmg_bonus;
}

// The chance of not burning a charge from a wand is based on Wandcraft alone.
int WandCalculator::calc_pct_chance_free_charge(CreaturePtr creature)
{
  int pct_chance_free_charge = 0;

  if (creature != nullptr)
  {
    int wand_val = creature->get_skills().get_value(SkillType::SKILL_GENERAL_WANDCRAFT);
    pct_chance_free_charge = wand_val / FREE_CHARGE_SKILL_DIVISOR;
  }

  return pct_chance_free_charge;
}

#ifdef UNIT_TESTS
#include "unit_tests/WandCalculator_test.cpp"
#endif