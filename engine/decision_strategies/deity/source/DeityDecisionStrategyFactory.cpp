#include <boost/make_shared.hpp>
#include "DeityDecisionStrategyFactory.hpp"
#include "DeityDecisionStrategy.hpp"

using boost::make_shared;

DeityDecisionStrategyFactory::DeityDecisionStrategyFactory()
{
}

DeityDecisionStrategyFactory::~DeityDecisionStrategyFactory()
{
}

IDeityDecisionStrategyPtr DeityDecisionStrategyFactory::create_deity_decision_strategy()
{
  IDeityDecisionStrategyPtr deity_decision_strategy = make_shared<DeityDecisionStrategy>();

  return deity_decision_strategy;
}
