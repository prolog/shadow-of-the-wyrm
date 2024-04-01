#include "WandCalculator.hpp"

using namespace std;

const int WandCalculator::DAMAGE_BONUS_STAT_DIVISOR = 15;
const int WandCalculator::DAMAGE_BONUS_SKILL_DIVISOR = 5;
const int WandCalculator::FREE_CHARGE_SKILL_DIVISOR = 10;
const int WandCalculator::DEFAULT_SPELL_CASTINGS_PER_CHARGE = 10;
const int WandCalculator::MIN_SPELL_CASTINGS_PER_CHARGE = 2;
const int WandCalculator::NUM_CHARGE_DIVISOR = 15;
const int WandCalculator::WANDCRAFT_RECHARGE_DIVISOR = 33;
const int WandCalculator::BASE_PCT_CHANCE_EXPLODE_CURSED = 1;
const int WandCalculator::WANDCRAFT_THRESHOLD_CAN_EXPLODE = 50;

// Wands have a 1% chance of exploding when cursed, further modified by the
// Wandcraft skill.
pair<int, int> WandCalculator::calc_x_in_y_chance_explode(CreaturePtr creature, ItemPtr wand)
{
  pair<int, int> no_explode = { 0,1 };
  auto chance = no_explode;

  if (wand != nullptr && wand->get_status() == ItemStatus::ITEM_STATUS_CURSED)
  {
    chance = { 1, 100 };
    float wandcraft_mult = 1.0f;

    if (creature != nullptr)
    {
      int wandcraft = creature->get_skills().get_value(SkillType::SKILL_GENERAL_WANDCRAFT);

      if (wandcraft <= WANDCRAFT_THRESHOLD_CAN_EXPLODE)
      {
        chance.second += (4 * wandcraft);
      }
      else
      {
        chance = no_explode;
      }
    }
  }

  return chance;
}

int WandCalculator::calc_explosion_damage(WandPtr wand)
{
  int dam = 0;

  if (wand != nullptr)
  {
    dam = 3 * wand->get_charges().get_current();
  }

  return dam;
}

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

int WandCalculator::calc_max_recharge_charges(CreaturePtr creature, ItemStatus item_status)
{
  int num_charges = 0;

  if (creature != nullptr)
  {
    switch (item_status)
    {
      case ItemStatus::ITEM_STATUS_BLESSED:
        num_charges = 3;
        break;
      case ItemStatus::ITEM_STATUS_CURSED:
        num_charges = 1;
        break;
      case ItemStatus::ITEM_STATUS_UNCURSED:
      default:
        num_charges = 2;
        break;
    }

    int wandcraft_bonus = creature->get_skills().get_value(SkillType::SKILL_GENERAL_WANDCRAFT) / WANDCRAFT_RECHARGE_DIVISOR;
    num_charges += wandcraft_bonus;
  }

  return num_charges;
}

#ifdef UNIT_TESTS
#include "unit_tests/WandCalculator_test.cpp"
#endif