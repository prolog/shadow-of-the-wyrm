#include "PhaseOfMoonCalculator.hpp"

using namespace std;

const int PhaseOfMoonCalculator::DAYS_PER_CYCLE = 28;
const map<int, PhaseOfMoonType> PhaseOfMoonCalculator::PHASE_THRESHOLDS = {{0, PhaseOfMoonType::PHASE_OF_MOON_NEW}, 
                                                                           {1, PhaseOfMoonType::PHASE_OF_MOON_WAXING}, 
                                                                           {13, PhaseOfMoonType::PHASE_OF_MOON_FULL}, 
                                                                           {14, PhaseOfMoonType::PHASE_OF_MOON_WANING}};

PhaseOfMoonType PhaseOfMoonCalculator::calculate_phase_of_moon(const double seconds) const
{
  PhaseOfMoonType pom = PhaseOfMoonType::PHASE_OF_MOON_NEW;

  // Get the number of days
  int num_days = static_cast<int>(seconds) / 60 / 60 / 24;
  int day_in_cycle = num_days % DAYS_PER_CYCLE;

  for (const auto& phase_pair : PHASE_THRESHOLDS)
  {
    if (day_in_cycle >= phase_pair.first)
    {
      pom = phase_pair.second;
    }
  }

  return pom;
}

#ifdef UNIT_TESTS
#include "unit_tests/PhaseOfMoonCalculator_test.cpp"
#endif

