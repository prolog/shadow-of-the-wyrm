#include "DeityDecisionConstants.hpp"
#include "DeityDecisionStrategy.hpp"

#include "FullAPDeityDecisionStrategyHandler.hpp"
#include "FullHPDeityDecisionStrategyHandler.hpp"
#include "DislikeDeityDecisionStrategyHandler.hpp"
#include "DoNothingDeityDecisionStrategyHandler.hpp"
#include "RestoreStatusDeityDecisionStrategyHandler.hpp"

DeityDecisionStrategy::DeityDecisionStrategy()
{
  initialize_decisions();
}

void DeityDecisionStrategy::initialize_decisions()
{
  decisions.clear();

  IDeityDecisionStrategyHandlerPtr cur_decision = std::make_shared<FullHPDeityDecisionStrategyHandler>();
  decisions.push_back(cur_decision);

  cur_decision = std::make_shared<RestoreStatusDeityDecisionStrategyHandler>();
  decisions.push_back(cur_decision);

  cur_decision = std::make_shared<FullAPDeityDecisionStrategyHandler>();
  decisions.push_back(cur_decision);

  cur_decision = std::make_shared<DislikeDeityDecisionStrategyHandler>();
  decisions.push_back(cur_decision);
}

// Loop through the set of possible decisions.
// The first one that meets the necessary criteria is selected.
// If none meet their criteria, the deity does nothing.
IDeityDecisionStrategyHandlerPtr DeityDecisionStrategy::get_decision(CreaturePtr creature)
{
  // The default decision if nothing else is selected.
  IDeityDecisionStrategyHandlerPtr do_nothing = std::make_shared<DoNothingDeityDecisionStrategyHandler>();

  for (IDeityDecisionStrategyHandlerPtr decision : decisions)
  {
    if (decision->decide(creature))
    {
      return decision;
    }
  }

  return do_nothing;
}
