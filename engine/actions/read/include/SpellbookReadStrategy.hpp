#pragma once
#include "ReadStrategy.hpp"

class SpellbookReadStrategy : public ReadStrategy
{
  public:
    ActionCostValue read(CreaturePtr creature, ActionManager * const am, ReadablePtr readable);

  protected:
    ActionCostValue get_action_cost_value() const;
};

