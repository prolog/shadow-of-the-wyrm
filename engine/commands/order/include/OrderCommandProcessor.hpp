#pragma once
#include "ActionCost.hpp"
#include "Creature.hpp"

class OrderCommandProcessor
{
  public:
    static ActionCostValue process(CreaturePtr creature, Command* command);

  protected:
    OrderCommandProcessor();
    ~OrderCommandProcessor();
};
