#pragma once
#include "ActionCost.hpp"
#include "Creature.hpp"

// A command processor that processes exclusively magic-related
// commands.
class MagicCommandProcessor 
{
  public:
    static ActionCostValue process(CreaturePtr creature, Command* command);

  protected:
    MagicCommandProcessor();
    ~MagicCommandProcessor();
};
