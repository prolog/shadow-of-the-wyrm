#include "ThreatRatings.hpp"

using std::string;
using std::map;
using std::set;

ThreatRatings::ThreatRatings()
{
}

ThreatRatings::~ThreatRatings()
{
}

// Check to see if a particular creature ID exists at any threat level
bool ThreatRatings::has_threat(const string& creature_id) const
{
  for (ThreatMap::const_iterator c_it = threat_ratings.begin(); c_it != threat_ratings.end(); c_it++)
  {
    set<string> threats_at_current_level = c_it->second;
    
    if (threats_at_current_level.find(creature_id) != threats_at_current_level.end())
    {
      return true;
    }
  }
  
  return false;
}

// Add a threat at a given threat rating.
void ThreatRatings::add_threat(const string& creature_id, const int threat_rating)
{
  ThreatMap::iterator t_it = threat_ratings.find(threat_rating);
  
  if (t_it != threat_ratings.end())
  {
    set<string>& threats = t_it->second;
    threats.insert(creature_id);
  }
  else
  {
    set<string> threats;
    threats.insert(creature_id);
    threat_ratings.insert(make_pair(threat_rating, threats));
  }
}

// Update a creature's threat rating by deleting the old, and adding the new.
void ThreatRatings::update_threat(const string& creature_id, const int old_threat_rating, const int new_threat_rating)
{
  remove_threat(creature_id, old_threat_rating);
  add_threat(creature_id, new_threat_rating);
}

// Remove a creature from the list of threat ratings.
void ThreatRatings::remove_threat(const string& creature_id, const int threat_rating)
{
  ThreatMap::iterator t_it = threat_ratings.find(threat_rating);
  
  if (t_it != threat_ratings.end())
  {
    set<string>& threats = t_it->second;
    threats.erase(creature_id);
  }
}

// Get all the threats.
ThreatMap ThreatRatings::get_all_threats() const
{
  return threat_ratings;
}
