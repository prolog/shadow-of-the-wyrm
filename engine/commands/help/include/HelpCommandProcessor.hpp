#pragma once
#include "ActionCost.hpp"
#include "Creature.hpp"

class HelpCommandProcessor
{
  public:
    static ActionCostValue process(CreaturePtr creature, CommandPtr command);

  protected:
    HelpCommandProcessor();
    ~HelpCommandProcessor();
};
