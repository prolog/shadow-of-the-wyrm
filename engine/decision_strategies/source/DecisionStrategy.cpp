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

// Set and get the current FOV map
void DecisionStrategy::set_fov_map(boost::shared_ptr<Map> new_fov_map)
{
  current_fov_map = new_fov_map;
}

boost::shared_ptr<Map> DecisionStrategy::get_fov_map()
{
  return current_fov_map;
}

