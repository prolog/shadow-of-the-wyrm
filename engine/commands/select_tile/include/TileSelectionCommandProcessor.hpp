#pragma once
#include <utility>
#include "ActionCost.hpp"
#include "Creature.hpp"
#include "TileSelectionCommands.hpp"
#include "TileSelectionAction.hpp"

// A command processor used for tile selection
//
// This class is a little different from some of the other command processors.  It
// returns a pair: the first element of the pair is whether to allow the creature
// to continue selecting tiles (so if the value is false, stop selecting tiles:
// e.g., tile has been selected, cancel has been selected).  The second element is
// the action cost value.
class TileSelectionCommandProcessor
{
  public:
    static std::pair<bool, ActionCostValue> process(CreaturePtr creature, CommandPtr command, TileSelectionAction* const tsa);

  protected:
    TileSelectionCommandProcessor();
    ~TileSelectionCommandProcessor();
    
    static std::pair<bool, ActionCostValue> process_cursor_directional_command(CreaturePtr creature, CursorDirectionalCommandPtr cursor_command, TileSelectionAction* const tsa);
};
