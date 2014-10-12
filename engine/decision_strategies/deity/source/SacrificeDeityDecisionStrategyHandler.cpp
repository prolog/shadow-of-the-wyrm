#include "DeityTextKeys.hpp"
#include "ItemPietyCalculator.hpp"
#include "SacrificeDeityDecisionStrategyHandler.hpp"

using std::string;

SacrificeDeityDecisionStrategyHandler::SacrificeDeityDecisionStrategyHandler()
{
}

SacrificeDeityDecisionStrategyHandler::SacrificeDeityDecisionStrategyHandler(ItemPtr sacrificed_item)
: sac_item(sacrificed_item)
{
}

bool SacrificeDeityDecisionStrategyHandler::decide(CreaturePtr creature)
{
  return true;
}

DeityDecisionImplications SacrificeDeityDecisionStrategyHandler::handle_decision(CreaturePtr creature, TilePtr tile)
{
  return get_deity_decision_implications(creature, tile);
}

// In this case, the piety loss is negative - so, a gain - due to the
// creature sacrificing some item for the glory of the deity.
int SacrificeDeityDecisionStrategyHandler::get_piety_loss() const
{
  ItemPietyCalculator ipc;
  int calc_piety = 0;

  if (sac_item)
  {
    calc_piety = ipc.calculate_piety(sac_item);
  }

  return (calc_piety * -1);
}

string SacrificeDeityDecisionStrategyHandler::get_message_sid() const
{
  string message_sid;

  // JCD FIXME

  return message_sid;
}

