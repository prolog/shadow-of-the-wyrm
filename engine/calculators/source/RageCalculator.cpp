#include "RageCalculator.hpp"
#include "Random.hpp"

const int RageCalculator::BASE_RAGE_DURATION_MEAN = 10;

int RageCalculator::calculate_duration_in_minutes(CreaturePtr /*creature*/) const
{
  PoissonDistribution p(BASE_RAGE_DURATION_MEAN);
  int duration = p.next();

  return duration;
}

// Always fires
int RageCalculator::calculate_pct_chance_effect(CreaturePtr /*creature*/) const
{
  return 100;
}