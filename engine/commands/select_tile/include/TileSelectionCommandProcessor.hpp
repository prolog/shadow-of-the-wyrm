#pragma once
#include <utility>
#include "ActionCost.hpp"
#include "Creature.hpp"
#include "SelectTileTypes.hpp"
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
    static std::pair<bool, ActionCostValue> process(CreaturePtr creature, Command* command, TileSelectionAction* const tsa);

  protected:
    TileSelectionCommandProcessor();
    virtual ~TileSelectionCommandProcessor();
    
    static std::pair<bool, ActionCostValue> process_cursor_directional_command(CreaturePtr creature, CursorDirectionalCommand* cursor_command, TileSelectionAction* const tsa);
    static std::pair<bool, ActionCostValue> process_tile_selection_bestiary(CreaturePtr creature, TileSelectionAction* const tsa);
    static std::pair<bool, ActionCostValue> process_tile_selection_item_codex(CreaturePtr creature, TileSelectionAction* const tsa);
    static std::pair<bool, ActionCostValue> process_tile_selection_by_creature(CreaturePtr creature, const SelectCreatureType sct, TileSelectionAction* const tsa);
    static std::pair<bool, ActionCostValue> process_tile_selection_order(CreaturePtr creature, TileSelectionAction* const tsa);
};
