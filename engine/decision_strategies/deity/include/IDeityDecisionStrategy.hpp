#pragma once
#include <memory>
#include "IDeityDecisionStrategyHandler.hpp"
#include "Creature.hpp"

class IDeityDecisionStrategy
{
  public:
    virtual IDeityDecisionStrategyHandlerPtr get_decision(CreaturePtr creature) = 0;
};

typedef std::shared_ptr<IDeityDecisionStrategy> IDeityDecisionStrategyPtr;

