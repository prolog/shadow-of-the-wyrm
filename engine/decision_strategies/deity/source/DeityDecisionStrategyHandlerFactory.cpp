#include <boost/make_shared.hpp>
#include "DeityDecisionStrategyHandlerFactory.hpp"
#include "DislikeDeityDecisionStrategyHandler.hpp"
#include "DoNothingDeityDecisionStrategyHandler.hpp"
#include "FullHPDeityDecisionStrategyHandler.hpp"

DeityDecisionStrategyHandlerFactory::DeityDecisionStrategyHandlerFactory()
{
}

DeityDecisionStrategyHandlerFactory::~DeityDecisionStrategyHandlerFactory()
{
}

IDeityDecisionStrategyHandlerPtr DeityDecisionStrategyHandlerFactory::create_decision_strategy_handler(const DeityDecisionType decision_type)
{
  IDeityDecisionStrategyHandlerPtr decision_handler;

  switch(decision_type)
  {
    case DEITY_DECISION_FULL_HP:
      decision_handler = boost::make_shared<FullHPDeityDecisionStrategyHandler>();
      break;
    case DEITY_DECISION_NOTHING:
    default:
      decision_handler = boost::make_shared<DoNothingDeityDecisionStrategyHandler>();
      break;
  }

  return decision_handler;
}

IDeityDecisionStrategyHandlerPtr DeityDecisionStrategyHandlerFactory::create_dislike_decision_strategy_handler()
{
  // Currently, all disliked actions will affect piety by the same amount.
  // This could change in future.
  IDeityDecisionStrategyHandlerPtr dislike_decision = boost::make_shared<DislikeDeityDecisionStrategyHandler>();

  return dislike_decision;
}

