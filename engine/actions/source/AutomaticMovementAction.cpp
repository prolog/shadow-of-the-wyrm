#include "AutomaticMovementAction.hpp"

using std::string;

AutomaticMovementAction::AutomaticMovementAction()
{
}

ActionCostValue AutomaticMovementAction::automatic_movement(CreaturePtr creature) const
{
  return get_action_cost_value();
}

ActionCostValue AutomaticMovementAction::get_action_cost_value() const
{
  return 1;
}

