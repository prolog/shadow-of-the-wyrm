#include "DecisionStrategy.hpp"

// Get the threats - used to determine a course of action.
ThreatRatings& DecisionStrategy::get_threats_ref()
{
  return threat_ratings;
}

// Get a copy of the threats.
ThreatRatings DecisionStrategy::get_threats() const
{
  return threat_ratings;
}
