#pragma once
#include "DecisionStrategy.hpp"

class DecisionStrategyFactory
{
  public:
    static DecisionStrategyPtr create_decision_strategy(const std::string& decision_strategy_id);

  protected:
    DecisionStrategyFactory();
    ~DecisionStrategyFactory();
};
