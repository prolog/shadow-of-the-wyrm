#pragma once
#include "IDeityDecisionStrategy.hpp"

class DeityDecisionStrategyFactory
{
  public:
    static IDeityDecisionStrategyPtr create_deity_decision_strategy(const std::string& deity_id);

  protected:
    DeityDecisionStrategyFactory();
    ~DeityDecisionStrategyFactory();
};
