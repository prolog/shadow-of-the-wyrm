#pragma once
#include <string>

class DecisionStrategyID
{
  public:
    static std::string DECISION_STRATEGY_DEFAULT;
    static std::string DECISION_STRATEGY_IMMOBILE;

  protected:
    DecisionStrategyID();
    ~DecisionStrategyID();
};
