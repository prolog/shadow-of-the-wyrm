#pragma once
#include <boost/shared_ptr.hpp>
#include "Command.hpp"

// Abstract base class for all other decision strategies.
class DecisionStrategy
{
  public:
    virtual CommandPtr get_decision() = 0;
};

typedef boost::shared_ptr<DecisionStrategy> DecisionStrategyPtr;
