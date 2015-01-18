#include "ModifyStatisticsCalculator.hpp"
#include "Random.hpp"

const int ModifyStatisticsCalculator::BASE_MODIFY_STATISTICS_DURATION_MEAN = 20;

// Calculate the duration in minutes.
int ModifyStatisticsCalculator::calculate_duration() const
{
  // Statistics modification lasts around twenty minutes.
  PoissonDistribution p(BASE_MODIFY_STATISTICS_DURATION_MEAN);
  int duration = p.next();

  return duration;
}

