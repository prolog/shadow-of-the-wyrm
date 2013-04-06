#include "DeityTextKeys.hpp"
#include "FullHPDeityDecisionStrategyHandler.hpp"

using std::string;

const int FullHPDeityDecisionStrategyHandler::PIETY_LOSS = 300;

DeityDecisionImplications FullHPDeityDecisionStrategyHandler::handle_decision(CreaturePtr creature)
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

  return get_deity_decision_implications();
}

int FullHPDeityDecisionStrategyHandler::get_piety_loss() const
{
  return PIETY_LOSS;
}

string FullHPDeityDecisionStrategyHandler::get_message_sid() const
{
  return DeityTextKeys::PRAYER_FULL_HP;
}
