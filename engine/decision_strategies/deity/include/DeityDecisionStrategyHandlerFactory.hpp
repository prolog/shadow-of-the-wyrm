#pragma once
#include "DeityDecisionTypes.hpp"
#include "IDeityDecisionStrategyHandler.hpp"

class DeityDecisionStrategyHandlerFactory
{
  public:
    static IDeityDecisionStrategyHandlerPtr create_decision_strategy_handler(const DeityDecisionType decision_type);

  protected:
    DeityDecisionStrategyHandlerFactory();
    ~DeityDecisionStrategyHandlerFactory();
};
