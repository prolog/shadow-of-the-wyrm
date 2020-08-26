#pragma once
#include <string>

class DecisionStrategyProperties
{
  public:
    static const std::string DECISION_STRATEGY_SUPPRESS_MAGIC;
    static const std::string DECISION_STRATEGY_BREEDS;

    // The difference between SENTINEL and ORDERED_SENTINEL is that the
    // former is permanent, and the second a flag set via a leader's
    // orders.
    static const std::string DECISION_STRATEGY_SENTINEL;
    static const std::string DECISION_STRATEGY_ORDERED_SENTINEL;
    
    static const std::string DECISION_STRATEGY_PICKUP;
    static const std::string DECISION_STRATEGY_SHOPKEEPER;
    static const std::string DECISION_STRATEGY_RESIST_SWITCH;
    static const std::string DECISION_STRATEGY_AUTOMOVE_COORDINATES;
    static const std::string DECISION_STRATEGY_SEARCH_PCT;
    static const std::string DECISION_STRATEGY_FOLLOW_CREATURE_ID;
    static const std::string DECISION_STRATEGY_ATTACK_CREATURES_THREATENING_ID;

  protected:
    DecisionStrategyProperties();
    ~DecisionStrategyProperties();
};

