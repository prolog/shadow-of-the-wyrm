#include "SpellcastingAction.hpp"
SpellcastingAction::SpellcastingAction()
{
}

ActionCostValue SpellcastingAction::cast_spell(CreaturePtr creature) const
{
  return get_action_cost_value();
}

ActionCostValue SpellcastingAction::get_action_cost_value() const
{
  return 1;
}