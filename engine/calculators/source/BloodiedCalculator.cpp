#include "BloodiedCalculator.hpp"
#include "Random.hpp"

const int BloodiedCalculator::BASE_BLOODIED_DURATION_MEAN = 4;
const int BloodiedCalculator::BASE_BLOODIED_PCT_CHANCE = 15;

// For every 7 points of strength, the percent chance of being bloodied
// decreases by 1.
const int BloodiedCalculator::BASE_BLOODIED_CHANCE_STRENGTH_MODIFIER = 7;

// Calculate the chance that this creature gets bloodied by the slash.
int BloodiedCalculator::calculate_pct_chance_effect(CreaturePtr creature) const
{
  int pct_chance = BASE_BLOODIED_PCT_CHANCE;

  if (creature)
  {
    int strength_bonus = creature->get_strength().get_current() / BASE_BLOODIED_CHANCE_STRENGTH_MODIFIER;

    double slash_multiplier = std::max<double>(0.0, creature->get_resistances().get_resistance_value(DamageType::DAMAGE_TYPE_SLASH));

    pct_chance -= strength_bonus;
    pct_chance = static_cast<int>(pct_chance * slash_multiplier);
  }

  return pct_chance;
}

int BloodiedCalculator::calculate_duration_in_minutes(CreaturePtr creature) const
{
  PoissonDistribution p(BASE_BLOODIED_DURATION_MEAN);
  int duration = p.next();

  return duration;
}

#ifdef UNIT_TESTS
#include "unit_tests/BloodiedCalculator_test.cpp"
#endif
