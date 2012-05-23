#pragma once
#include <boost/shared_ptr.hpp>
#include "Command.hpp"
#include "CommandFactory.hpp"
#include "KeyboardCommandMap.hpp"
#include "Map.hpp"

class Map;

// Abstract base class for all other decision strategies.
class DecisionStrategy
{
  public:
    virtual CommandPtr get_decision(CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands, boost::shared_ptr<Map> view_map = boost::shared_ptr<Map>() /* optional - only used when getting a decision on the main map, and only for non-player characters. */) = 0;
    virtual bool get_confirmation() = 0;
};

typedef boost::shared_ptr<DecisionStrategy> DecisionStrategyPtr;
