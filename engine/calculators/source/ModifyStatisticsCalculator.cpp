#include "ModifyStatisticsCalculator.hpp"
#include "Random.hpp"

const int ModifyStatisticsCalculator::BASE_MODIFY_STATISTICS_DURATION_MEAN = 60;

// Calculate the duration in minutes.
int ModifyStatisticsCalculator::calculate_duration() const
{
  // Statistics modification lasts around an hour or so.
  PoissonDistribution p(BASE_MODIFY_STATISTICS_DURATION_MEAN);
  int duration = p.next();

  return duration;
}

