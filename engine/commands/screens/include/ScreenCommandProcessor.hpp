#pragma once
#include "ActionCost.hpp"
#include "Creature.hpp"

// A command processor that processes commands common to all screens
// (paging, etc).
class ScreenCommandProcessor 
{
  public:
    static ActionCostValue process(CreaturePtr creature, CommandPtr command);

  protected:
    ScreenCommandProcessor();
    ~ScreenCommandProcessor();
};
