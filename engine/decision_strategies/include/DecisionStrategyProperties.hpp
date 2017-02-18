#pragma once
#include <string>

class DecisionStrategyProperties
{
  public:
    static const std::string DECISION_STRATEGY_SUPPRESS_MAGIC;
    static const std::string DECISION_STRATEGY_BREEDS;
    static const std::string DECISION_STRATEGY_SENTINEL;
    static const std::string DECISION_STRATEGY_SHOPKEEPER;
    static const std::string DECISION_STRATEGY_RESIST_SWITCH;

  protected:
    DecisionStrategyProperties();
    ~DecisionStrategyProperties();
};

