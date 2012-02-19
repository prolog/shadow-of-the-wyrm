#pragma once
#include <boost/shared_ptr.hpp>
#include "Command.hpp"
#include "CommandFactory.hpp"
#include "KeyboardCommandMap.hpp"

// Abstract base class for all other decision strategies.
class DecisionStrategy
{
  public:
    virtual CommandPtr get_decision(CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands) = 0;
    virtual bool get_confirmation() = 0;
};

typedef boost::shared_ptr<DecisionStrategy> DecisionStrategyPtr;
