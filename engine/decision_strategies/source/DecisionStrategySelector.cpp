#include "AutomaticMovementDecisionStrategy.hpp"
#include "DecisionStrategySelector.hpp"

// Determine whether to use the creature's existing decision strategy,
// or another one based on particular attributes of the creature
// (automovement, etc).
DecisionStrategyPtr DecisionStrategySelector::select_decision_strategy(CreaturePtr creature)
{
  DecisionStrategyPtr decision;

  if (creature)
  {
    if (creature->get_automatic_movement_ref().get_engaged())
    {
      decision = std::make_shared<AutomaticMovementDecisionStrategy>(creature->get_automatic_movement_ref(), creature->get_decision_strategy()->get_controller());
    }
    else
    {
      decision = creature->get_decision_strategy();
    }
  }

  return decision;
}

#ifdef UNIT_TESTS
#include "unit_tests/DecisionStrategySelector_test.cpp"
#endif