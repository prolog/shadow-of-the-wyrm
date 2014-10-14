#include "DeityDecisionConstants.hpp"
#include "DeityTextKeys.hpp"
#include "FullAPDeityDecisionStrategyHandler.hpp"

using std::string;

FullAPDeityDecisionStrategyHandler::FullAPDeityDecisionStrategyHandler(const string& new_deity_id)
: DeityDecisionStrategyHandler(new_deity_id)
{
}

bool FullAPDeityDecisionStrategyHandler::decide(CreaturePtr creature)
{
  bool decision = false;

  if (creature)
  {
    Statistic ap = creature->get_arcana_points();

    if (ap.get_current() < (ap.get_base() * DeityDecisionConstants::HEAL_AP_MAX_PCT))
    {
      decision = true;
    }
  }

  return decision;
}

DeityDecisionImplications FullAPDeityDecisionStrategyHandler::handle_decision(CreaturePtr creature, TilePtr tile)
{
  if (creature)
  {
    Statistic arc_points = creature->get_arcana_points();
    int base_ap          = arc_points.get_base();
    int current_ap       = arc_points.get_current();

    if (current_ap < base_ap)
    {
      arc_points.set_current(base_ap);
      creature->set_arcana_points(arc_points);
    }
  }

  return get_deity_decision_implications(creature, tile);
}

// Slightly less piety loss than yelling,
// "HEY IMMS, I COULD USE A HEAL!"
int FullAPDeityDecisionStrategyHandler::get_piety_loss() const
{
  return 400;
}

string FullAPDeityDecisionStrategyHandler::get_message_sid() const
{
  return DeityTextKeys::PRAYER_FULL_AP;
}
