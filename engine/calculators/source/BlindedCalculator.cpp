#include "BlindedCalculator.hpp"
#include "Random.hpp"

const int BlindedCalculator::BASE_BLINDED_DURATION_MEAN = 3;
const int BlindedCalculator::BASE_BLINDED_PCT_CHANCE = 15;

// For every 7 points of health, the percent chance of being blinded
// decreases by 1.
const int BlindedCalculator::BASE_BLINDED_CHANCE_HEALTH_MODIFIER = 7;

int BlindedCalculator::calculate_pct_chance_effect(CreaturePtr creature) const
{
  int pct_chance = BASE_BLINDED_PCT_CHANCE;

  if (creature)
  {
    int health_bonus = creature->get_health().get_current() / BASE_BLINDED_CHANCE_HEALTH_MODIFIER;

    double fire_multiplier = std::max<double>(0.0, creature->get_resistances().get_resistance_value(DamageType::DAMAGE_TYPE_HEAT));

    pct_chance -= health_bonus;
    pct_chance = static_cast<int>(pct_chance * fire_multiplier);
  }

  return pct_chance;
}

int BlindedCalculator::calculate_duration_in_minutes(CreaturePtr creature) const
{
  PoissonDistribution p(BASE_BLINDED_DURATION_MEAN);
  int duration = p.next();

  return duration;
}

#ifdef UNIT_TESTS
#include "unit_tests/BlindedCalculator_test.cpp"
#endif
