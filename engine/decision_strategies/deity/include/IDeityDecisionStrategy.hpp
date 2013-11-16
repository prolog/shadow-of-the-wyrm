#pragma once
#include <boost/shared_ptr.hpp>
#include "IDeityDecisionStrategyHandler.hpp"
#include "Creature.hpp"

class IDeityDecisionStrategy
{
  public:
    virtual IDeityDecisionStrategyHandlerPtr get_decision(CreaturePtr creature) = 0;
};

typedef boost::shared_ptr<IDeityDecisionStrategy> IDeityDecisionStrategyPtr;

