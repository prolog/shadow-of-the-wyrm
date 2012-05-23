#pragma once
#include <map>
#include <string>
#include <set>

// Shorthand for easy typin'.
typedef std::map<int, std::set<std::string> > ThreatMap;

// ThreatRatings is a class representing the threat rating of various
// creatures.
class ThreatRatings
{
  public:
    ThreatRatings();
    ~ThreatRatings();
    
    void add_threat(const std::string& creature_id, const int threat_rating);
    void update_threat(const std::string& creature_id, const int old_threat_rating, const int new_threat_rating);
    void remove_threat(const std::string& creature_id, const int threat_rating);
    
    ThreatMap get_all_threats() const;

  protected:
    ThreatMap threat_ratings;
};
