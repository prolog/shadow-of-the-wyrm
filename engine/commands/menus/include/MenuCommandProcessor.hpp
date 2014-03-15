#pragma once
#include "ActionCost.hpp"
#include "Creature.hpp"

// A command processor that processes commands common to all menus
// (paging, etc).
class MenuCommandProcessor 
{
  public:
    static ActionCostValue process(CreaturePtr creature, CommandPtr command);

  protected:
    MenuCommandProcessor();
    ~MenuCommandProcessor();
};
