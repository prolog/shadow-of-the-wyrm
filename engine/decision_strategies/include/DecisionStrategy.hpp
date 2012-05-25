#pragma once
#include <boost/shared_ptr.hpp>
#include "Command.hpp"
#include "CommandFactory.hpp"
#include "KeyboardCommandMap.hpp"
#include "Map.hpp"
#include "ThreatRatings.hpp"

class Map;

// Abstract base class for all other decision strategies.
class DecisionStrategy
{
  public:
    virtual CommandPtr get_decision(const std::string& this_creature_id, CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands, boost::shared_ptr<Map> view_map = boost::shared_ptr<Map>() /* optional - only used when getting a decision on the main map, and only for non-player characters. */) = 0;
    virtual bool get_confirmation() = 0;

    ThreatRatings& get_threats_ref();
    ThreatRatings  get_threats() const;

  protected:
    ThreatRatings threat_ratings;
};

typedef boost::shared_ptr<DecisionStrategy> DecisionStrategyPtr;
