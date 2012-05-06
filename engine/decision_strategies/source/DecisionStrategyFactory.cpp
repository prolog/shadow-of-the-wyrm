#include <boost/make_shared.hpp>
#include "DecisionStrategyFactory.hpp"
#include "DecisionStrategyTypes.hpp"
#include "ImmobileDecisionStrategy.hpp"
#include "NullKeyboardController.hpp"

using std::string;
using boost::make_shared;

DecisionStrategyFactory::DecisionStrategyFactory()
{
}

DecisionStrategyFactory::~DecisionStrategyFactory()
{
}

// Create the decision strategy based on the passed-in decision strategy
// identifier.
DecisionStrategyPtr DecisionStrategyFactory::create_decision_strategy(const string& decision_strategy_id)
{
  DecisionStrategyPtr strategy;
  ControllerPtr controller;
  controller = make_shared<NullKeyboardController>();
  
  if (decision_strategy_id == DecisionStrategyID::DECISION_STRATEGY_IMMOBILE)
  {
    strategy = make_shared<ImmobileDecisionStrategy>(controller);
  }
  // ??? == PLAYER?  Could be interesting...
  else // Assume == DecisionStrategyID::DECISION_STRATEGY_DEFAULT
  {
//    strategy = make_shared<DefaultDecisionStrategy>();
  }
  
  return strategy;
}

