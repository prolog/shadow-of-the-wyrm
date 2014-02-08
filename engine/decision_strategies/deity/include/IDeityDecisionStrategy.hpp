#pragma once
#include <memory>
#include "DeityDecisionStrategyHandler.hpp"
#include "Creature.hpp"

class IDeityDecisionStrategy
{
  public:
    virtual DeityDecisionStrategyHandlerPtr get_decision(CreaturePtr creature) = 0;
};

typedef std::shared_ptr<IDeityDecisionStrategy> IDeityDecisionStrategyPtr;

