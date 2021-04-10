#include "AutomaticActionsAction.hpp"

ActionCostValue AutomaticActionsAction::automatic_actions() const
{
  return get_action_cost_value(nullptr);
}

ActionCostValue AutomaticActionsAction::get_action_cost_value(CreaturePtr c) const
{
  return ActionCostConstants::NO_ACTION;
}
