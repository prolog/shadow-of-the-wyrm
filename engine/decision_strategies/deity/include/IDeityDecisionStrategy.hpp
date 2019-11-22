#pragma once
#include <memory>
#include "DeityDecisionStrategyHandler.hpp"
#include "Creature.hpp"
#include "Feature.hpp"

class IDeityDecisionStrategy
{
  public:
    virtual DeityDecisionStrategyHandlerPtr get_decision(CreaturePtr creature) = 0;
    virtual DeityDecisionStrategyHandlerPtr get_decision_for_sacrifice(CreaturePtr creature, ItemPtr item) = 0;
    virtual DeityDecisionStrategyHandlerPtr get_decision_for_altar_drop(CreaturePtr dropping_creature, FeaturePtr feature, ItemPtr item) = 0;
};

using IDeityDecisionStrategyPtr = std::unique_ptr<IDeityDecisionStrategy>;

