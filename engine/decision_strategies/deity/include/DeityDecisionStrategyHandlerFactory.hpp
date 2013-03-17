#pragma once
#include "DeityDecisionTypes.hpp"
#include "IDeityDecisionStrategyHandler.hpp"

class DeityDecisionStrategyHandlerFactory
{
  public:
    static IDeityDecisionStrategyHandlerPtr create_decision_strategy_handler(const DeityDecisionType decision_type);

    // Create a decision strategy handler for "disliked" creature actions.
    static IDeityDecisionStrategyHandlerPtr create_dislike_decision_strategy_handler();

  protected:
    DeityDecisionStrategyHandlerFactory();
    ~DeityDecisionStrategyHandlerFactory();
};
