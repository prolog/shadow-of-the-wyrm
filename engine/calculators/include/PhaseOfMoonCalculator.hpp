#pragma once
#include <map>
#include "CalendarTypes.hpp"

class PhaseOfMoonCalculator
{
  public:
    // Each full set of phases takes 29 days in the world of the wyrm.
    PhaseOfMoonType calculate_phase_of_moon(const double seconds) const;

  protected:
    static const int DAYS_PER_CYCLE;
    static const std::map<int, PhaseOfMoonType> PHASE_THRESHOLDS;
};

