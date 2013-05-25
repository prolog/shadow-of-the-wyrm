#include "SpellbookReadStrategy.hpp"

ActionCostValue SpellbookReadStrategy::read(CreaturePtr creature, ActionManager * const am, ReadablePtr readable)
{
  ActionCostValue acv = 0;

  if (creature && readable)
  {
    acv = get_action_cost_value();
  }

  return acv;
}

ActionCostValue SpellbookReadStrategy::get_action_cost_value() const
{
  return 1;
}

