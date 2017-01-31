#include "BuySellCalculator.hpp"

const int BuySellCalculator::PREMIUM_DISCOUNT_DIVISOR = 2;

// The percent chance to negotiate a discount or premium is directly
// proportional to a creature's Bargaining skill.
int BuySellCalculator::calc_pct_chance_bargain(CreaturePtr creature)
{
  int pct_chance = 0;

  if (creature != nullptr)
  {
    pct_chance = creature->get_skills().get_value_incr_marks(SkillType::SKILL_GENERAL_BARGAINING);
  }

  return pct_chance;
}

// Discounts and premiums are calculated as half the average of Charisma and
// Bargaining.
int BuySellCalculator::calc_pct_discount_buy(CreaturePtr creature)
{
  int pct_disc = get_prem_disc_percentage(creature);

  return pct_disc;
}

int BuySellCalculator::calc_pct_premium_sell(CreaturePtr creature)
{
  int pct_prem = get_prem_disc_percentage(creature);

  return pct_prem;
}

int BuySellCalculator::get_prem_disc_percentage(CreaturePtr creature)
{
  int pd_pct = 0;

  if (creature != nullptr)
  {
    pd_pct = (creature->get_charisma().get_current() + creature->get_skills().get_value(SkillType::SKILL_GENERAL_BARGAINING)) / 2;
    pd_pct = pd_pct / PREMIUM_DISCOUNT_DIVISOR;
  }

  return pd_pct;
}

#ifdef UNIT_TESTS
#include "unit_tests/BuySellCalculator_test.cpp"
#endif

