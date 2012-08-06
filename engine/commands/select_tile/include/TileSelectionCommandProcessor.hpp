#pragma once
#include "ActionCost.hpp"
#include "Creature.hpp"
#include "TileSelectionCommands.hpp"

// A command processor used for tile selection
class TileSelectionCommandProcessor
{
  public:
    static ActionCostValue process(CreaturePtr creature, CommandPtr command);

  protected:
    TileSelectionCommandProcessor();
    ~TileSelectionCommandProcessor();
    
    static ActionCostValue process_cursor_directional_command(CreaturePtr creature, CursorDirectionalCommandPtr cursor_command);
};
