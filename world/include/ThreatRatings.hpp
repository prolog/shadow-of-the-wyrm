#pragma once
#include <map>
#include <string>
#include <set>
#include "ISerializable.hpp"

using ThreatMap = std::map<int, std::set<std::string>>;

// ThreatRatings is a class representing the threat rating of various
// creatures.
class ThreatRatings : public ISerializable
{
  public:
    ThreatRatings();
    ~ThreatRatings();
    bool operator==(const ThreatRatings& threat_ratings) const;
    
    void clear();

    // Check to see if the creature is contained in any threat level.
    std::pair<bool, int> has_threat(const std::string& creature_id) const;
    void add_or_update_threat(const std::string& creature_id, const int threat_rating);
    void add_threat(const std::string& creature_id, const int threat_rating);
    void update_threat(const std::string& creature_id, const int old_threat_rating, const int new_threat_rating);
    void remove_threat(const std::string& creature_id, const int threat_rating);
    
    ThreatMap get_all_threats() const;

    // Returns only those threats that are above the "dislike" threshold.
    std::set<std::string> get_true_threats_without_level() const;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  protected:
    ThreatMap threat_ratings;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
