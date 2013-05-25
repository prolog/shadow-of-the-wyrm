#include "NullReadStrategy.hpp"

ActionCostValue NullReadStrategy::read(CreaturePtr creature, ActionManager * const am, ReadablePtr readable)
{
  return get_action_cost_value();
}

// Trying to read an unreadable type of item should never happen!
ActionCostValue NullReadStrategy::get_action_cost_value() const
{
  return 0;
}


