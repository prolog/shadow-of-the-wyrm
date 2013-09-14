#pragma once
#include "Creature.hpp"

// Given a creature, DecisionStrategySelector determines which decision
// strategy to use.  If automatic movement is engaged, an
// AutomaticMovementDecisionStrategy is created.  Otherwise, the creature's
// decision strategy is used.
class DecisionStrategySelector
{
  public:
    static DecisionStrategyPtr select_decision_strategy(CreaturePtr creature);
};

