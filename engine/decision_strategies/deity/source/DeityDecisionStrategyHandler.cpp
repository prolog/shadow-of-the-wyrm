#include "DeityDecisionStrategyHandler.hpp"

using namespace std;

DeityDecisionStrategyHandler::DeityDecisionStrategyHandler(const string& new_deity_id)
: deity_id(new_deity_id)
{
}

DeityDecisionImplications DeityDecisionStrategyHandler::get_deity_decision_implications(CreaturePtr creature, TilePtr tile) const
{
  int piety_loss = get_piety_loss();
  
  // Some tiles/features reduce the piety loss (e.g. when praying on an altar,
  // etc).  But this should affect only piety loss, and not piety gain.
  if (piety_loss > 0)
  {
    piety_loss = static_cast<int>(piety_loss * tile->get_piety_loss_multiplier());
  }

  DeityDecisionImplications decision_implications(piety_loss, get_message_sid());

  return decision_implications;
}
