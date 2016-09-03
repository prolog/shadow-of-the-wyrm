#include <algorithm>
#include "StatisticsMarker.hpp"
#include "RNG.hpp"

using namespace std;

StatisticsMarkerProbabilityDetails::StatisticsMarkerProbabilityDetails(const bool new_override_p_denom, const int new_p_denom)
: override_p_denom(new_override_p_denom), p_denom(new_p_denom)
{
}

bool StatisticsMarkerProbabilityDetails::get_override_p_denom() const
{
  return override_p_denom;
}

int StatisticsMarkerProbabilityDetails::get_p_denom() const
{
  return p_denom;
}

// Marks a statistic based on a declining probability, based on the 
// statistic's base value.
//
// Statistics are not marked if the number of marks is equal to the
// statistic's base value.
//
// Returns true if the statistic was marked, false otherwise.
bool StatisticsMarker::mark_statistic(Statistic& stat, const StatisticsMarkerProbabilityDetails& smpd)
{
  bool marked = false;
  Marks& marks = stat.get_marks_ref();
  int base_val = stat.get_base();

  if (marks.get_value() < base_val)
  {
    int x = 1;
    int y = smpd.get_p_denom();
    
    if (smpd.get_override_p_denom() == false)
    {
      calculate_mark_probability_denominator(base_val);
    }

    if (RNG::x_in_y_chance(x, y))
    {
      marks.incr();
    }
  }

  return marked;
}

bool StatisticsMarker::mark_strength(CreaturePtr creature, const StatisticsMarkerProbabilityDetails& smpd)
{
  bool marked = false;

  if (creature != nullptr)
  {
    marked = mark_statistic(creature->get_strength_ref(), smpd);
  }

  return marked;
}

bool StatisticsMarker::mark_dexterity(CreaturePtr creature, const StatisticsMarkerProbabilityDetails& smpd)
{
  bool marked = false;

  if (creature != nullptr)
  {
    marked = mark_statistic(creature->get_dexterity_ref(), smpd);
  }

  return marked;
}

bool StatisticsMarker::mark_agility(CreaturePtr creature, const StatisticsMarkerProbabilityDetails& smpd)
{
  bool marked = false;

  if (creature != nullptr)
  {
    marked = mark_statistic(creature->get_agility_ref(), smpd);
  }

  return marked;
}

bool StatisticsMarker::mark_health(CreaturePtr creature, const StatisticsMarkerProbabilityDetails& smpd)
{
  bool marked = false;

  if (creature != nullptr)
  {
    marked = mark_statistic(creature->get_health_ref(), smpd);
  }

  return marked;
}

bool StatisticsMarker::mark_intelligence(CreaturePtr creature, const StatisticsMarkerProbabilityDetails& smpd)
{
  bool marked = false;

  if (creature != nullptr)
  {
    marked = mark_statistic(creature->get_intelligence_ref(), smpd);
  }

  return marked;
}

bool StatisticsMarker::mark_willpower(CreaturePtr creature, const StatisticsMarkerProbabilityDetails& smpd)
{
  bool marked = false;

  if (creature != nullptr)
  {
    marked = mark_statistic(creature->get_willpower_ref(), smpd);
  }

  return marked;
}

bool StatisticsMarker::mark_charisma(CreaturePtr creature, const StatisticsMarkerProbabilityDetails& smpd)
{
  bool marked = false;

  if (creature != nullptr)
  {
    marked = mark_statistic(creature->get_charisma_ref(), smpd);
  }

  return marked;
}

// Calculates the y in the x-in-y chance that a stat is marked.
//
// The probability is 1 / (2 ^ (stat_base_val / 10)))
//
// This function means that marking statistics gets exponentially
// more difficult with every 10 points.
int StatisticsMarker::calculate_mark_probability_denominator(const int stat_base_value)
{
  int d = stat_base_value;

  if (d < 0)
  {
    d = 0;
  }

  int denom = static_cast<int>(std::pow(2, (d / 10)));
  return denom;
}

#ifdef UNIT_TESTS
#include "unit_tests/StatisticsMarker_test.cpp"
#endif
