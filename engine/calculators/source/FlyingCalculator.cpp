#include "FlyingCalculator.hpp"
#include "Random.hpp"

const int FlyingCalculator::BASE_FLYING_DURATION_MEAN = 45;
const int FlyingCalculator::BASE_FLYING_PCT_CHANCE = 100;

int FlyingCalculator::calculate_pct_chance_effect(CreaturePtr creature) const
{
  return BASE_FLYING_PCT_CHANCE;
}

int FlyingCalculator::calculate_duration_in_minutes(CreaturePtr creature) const
{
  PoissonDistribution p(BASE_FLYING_DURATION_MEAN);
  int duration = p.next();

  return duration;
}

