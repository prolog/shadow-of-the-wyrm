#include "IDeityDecisionStrategyHandler.hpp"

DeityDecisionImplications IDeityDecisionStrategyHandler::get_deity_decision_implications() const
{
  DeityDecisionImplications decision_implications(get_piety_loss(), get_message_sid());

  return decision_implications;
}
