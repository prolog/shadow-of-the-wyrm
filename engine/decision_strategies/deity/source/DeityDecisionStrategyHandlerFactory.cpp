#include <boost/make_shared.hpp>
#include "DeityDecisionStrategyHandlerFactory.hpp"
#include "DoNothingDeityDecisionStrategyHandler.hpp"

using boost::make_shared;

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
    case DEITY_DECISION_NOTHING:
    case DEITY_DECISION_FULL_HP:
    default:
      decision_handler = make_shared<DoNothingDeityDecisionStrategyHandler>();
      break;
  }

  return decision_handler;
}
