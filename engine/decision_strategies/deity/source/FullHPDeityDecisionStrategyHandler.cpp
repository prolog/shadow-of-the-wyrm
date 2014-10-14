#include "DeityDecisionConstants.hpp"
#include "DeityTextKeys.hpp"
#include "FullHPDeityDecisionStrategyHandler.hpp"

using std::string;

FullHPDeityDecisionStrategyHandler::FullHPDeityDecisionStrategyHandler(const string& new_deity_id)
: DeityDecisionStrategyHandler(new_deity_id)
{
}

bool FullHPDeityDecisionStrategyHandler::decide(CreaturePtr creature)
{
  bool decision = false;

  if (creature)
  {
    Statistic hp = creature->get_hit_points();

    if (hp.get_current() < (hp.get_base() * DeityDecisionConstants::HEAL_HP_MAX_PCT))
    {
      decision = true;
    }
  }

  return decision;
}

DeityDecisionImplications FullHPDeityDecisionStrategyHandler::handle_decision(CreaturePtr creature, TilePtr tile)
{
  if (creature)
  {
    Statistic hit_points = creature->get_hit_points();
    int base_hp          = hit_points.get_base();
    int current_hp       = hit_points.get_current();

    if (current_hp < base_hp)
    {
      hit_points.set_current(base_hp);
      creature->set_hit_points(hit_points);
    }
  }

  return get_deity_decision_implications(creature, tile);
}

int FullHPDeityDecisionStrategyHandler::get_piety_loss() const
{
  return 500;
}

string FullHPDeityDecisionStrategyHandler::get_message_sid() const
{
  return DeityTextKeys::PRAYER_FULL_HP;
}
