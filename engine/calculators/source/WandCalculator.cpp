#include "WandCalculator.hpp"

const int WandCalculator::DAMAGE_BONUS_STAT_DIVISOR = 15;
const int WandCalculator::DAMAGE_BONUS_SKILL_DIVISOR = 5;
const int WandCalculator::FREE_CHARGE_SKILL_DIVISOR = 10;
const int WandCalculator::DEFAULT_SPELL_CASTINGS_PER_CHARGE = 10;
const int WandCalculator::MIN_SPELL_CASTINGS_PER_CHARGE = 2;
const int WandCalculator::NUM_CHARGE_DIVISOR = 15;

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

// -1 usage per 10 points of Wandcraft, though the minimum of 2 castings/charge
// is enforced.
int WandCalculator::calc_spell_castings_per_charge(CreaturePtr creature)
{
  int castings = DEFAULT_SPELL_CASTINGS_PER_CHARGE;

  if (creature != nullptr)
  {
    int wandcraft_val = creature->get_skills().get_value(SkillType::SKILL_GENERAL_WANDCRAFT);
    castings -= (wandcraft_val / 10);
    castings = std::max<int>(castings, MIN_SPELL_CASTINGS_PER_CHARGE);
  }

  return castings;
}

// The number of charges that a caster can actually force into a knobby bit of
// wood is based half on intelligence, half on wandcraft - 1 charge (always),
// with +1 per 15 int and +1 per 15 wandcraft.
int WandCalculator::calc_num_charges(CreaturePtr creature)
{
  int num_charges = 1;

  if (creature != nullptr)
  {
    int int_val = creature->get_intelligence().get_current();
    int wandcraft_val = creature->get_skills().get_value(SkillType::SKILL_GENERAL_WANDCRAFT);

    num_charges += (int_val / NUM_CHARGE_DIVISOR);
    num_charges += (wandcraft_val / NUM_CHARGE_DIVISOR);
  }

  return num_charges;
}

#ifdef UNIT_TESTS
#include "unit_tests/WandCalculator_test.cpp"
#endif