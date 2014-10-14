#include "DeityDecisionStrategyFactory.hpp"
#include "DeityDecisionStrategy.hpp"

using namespace std;

DeityDecisionStrategyFactory::DeityDecisionStrategyFactory()
{
}

DeityDecisionStrategyFactory::~DeityDecisionStrategyFactory()
{
}

IDeityDecisionStrategyPtr DeityDecisionStrategyFactory::create_deity_decision_strategy(const string& deity_id)
{
  IDeityDecisionStrategyPtr deity_decision_strategy = std::make_shared<DeityDecisionStrategy>(deity_id);

  return deity_decision_strategy;
}
