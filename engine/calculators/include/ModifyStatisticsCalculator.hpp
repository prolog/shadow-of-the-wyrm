#pragma once

// Class that calculates the length of the Modify Statistics effect.
class ModifyStatisticsCalculator
{
  public:
    int calculate_duration() const;

  protected:
    static const int BASE_MODIFY_STATISTICS_DURATION_MEAN;
};


