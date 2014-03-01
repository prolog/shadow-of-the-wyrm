#include "Conversion.hpp"
#include "DeityDecisionConstants.hpp"
#include "DeityTextKeys.hpp"
#include "SatiateDeityDecisionStrategyHandler.hpp"

using std::string;

bool SatiateDeityDecisionStrategyHandler::decide(CreaturePtr creature)
{
  bool decision = false;

  if (creature)
  {
    // If the creature isn't full or greater, it's feedin' time.
    HungerClock& hc = creature->get_hunger_clock_ref();
    decision = hc.is_normal_or_worse();
  }

  return decision;
}

DeityDecisionImplications SatiateDeityDecisionStrategyHandler::handle_decision(CreaturePtr creature, TilePtr tile)
{
  if (creature)
  {
    HungerClock& hc = creature->get_hunger_clock_ref();
    hc.set_hunger(hc.get_hunger() + HungerLevelConverter::INT_HUNGER_LEVEL_STUFFED);
  }

  return get_deity_decision_implications(creature, tile);
}

// It takes the Nine a while to gather the manna...
int SatiateDeityDecisionStrategyHandler::get_piety_loss() const
{
  return 600;
}

string SatiateDeityDecisionStrategyHandler::get_message_sid() const
{
  return DeityTextKeys::PRAYER_SATIATE;
}
