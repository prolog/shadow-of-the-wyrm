#include "DeityDecisionStrategyHandler.hpp"

DeityDecisionImplications DeityDecisionStrategyHandler::get_deity_decision_implications(CreaturePtr creature, TilePtr tile) const
{
  int piety_loss = static_cast<int>(get_piety_loss() * tile->get_piety_loss_multiplier());

  DeityDecisionImplications decision_implications(piety_loss, get_message_sid());

  return decision_implications;
}
