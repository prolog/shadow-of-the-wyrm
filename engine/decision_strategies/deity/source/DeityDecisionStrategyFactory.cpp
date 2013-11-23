#include "DeityDecisionStrategyFactory.hpp"
#include "DeityDecisionStrategy.hpp"

DeityDecisionStrategyFactory::DeityDecisionStrategyFactory()
{
}

DeityDecisionStrategyFactory::~DeityDecisionStrategyFactory()
{
}

IDeityDecisionStrategyPtr DeityDecisionStrategyFactory::create_deity_decision_strategy()
{
  IDeityDecisionStrategyPtr deity_decision_strategy = std::make_shared<DeityDecisionStrategy>();

  return deity_decision_strategy;
}
