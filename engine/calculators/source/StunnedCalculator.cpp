#include "StunnedCalculator.hpp"
#include "Random.hpp"

const int StunnedCalculator::BASE_STUNNED_DURATION_MEAN = 3;
const int StunnedCalculator::BASE_STUNNED_PCT_CHANCE = 15;

// For every 7 points of dexterity, the percent chance of being stunned
// decreases by 1.
const int StunnedCalculator::BASE_STUNNED_CHANCE_DEXTERITY_MODIFIER = 7;

int StunnedCalculator::calculate_pct_chance_effect(CreaturePtr creature) const
{
  int pct_chance = BASE_STUNNED_PCT_CHANCE;

  if (creature)
  {
    int dexterity_bonus = creature->get_dexterity().get_current() / BASE_STUNNED_CHANCE_DEXTERITY_MODIFIER;

    double pound_multiplier = std::max<double>(0.0, creature->get_resistances().get_resistance_value(DamageType::DAMAGE_TYPE_POUND));

    pct_chance -= dexterity_bonus;
    pct_chance = static_cast<int>(pct_chance * pound_multiplier);
  }

  return pct_chance;
}

int StunnedCalculator::calculate_duration_in_minutes(CreaturePtr creature) const
{
  PoissonDistribution p(BASE_STUNNED_DURATION_MEAN);
  int duration = p.next();

  return duration;
}

#ifdef UNIT_TESTS
#include "unit_tests/StunnedCalculator_test.cpp"
#endif
