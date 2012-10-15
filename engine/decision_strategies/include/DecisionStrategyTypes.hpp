#pragma once
#include <string>

class DecisionStrategyID
{
  public:
    static std::string DECISION_STRATEGY_DEFAULT;
    static std::string DECISION_STRATEGY_IMMOBILE;
    static std::string DECISION_STRATEGY_MOBILE;
    static std::string DECISION_STRATEGY_PLAYER;

  protected:
    DecisionStrategyID();
    ~DecisionStrategyID();
};
