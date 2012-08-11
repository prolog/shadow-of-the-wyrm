#pragma once
#include "IActionManager.hpp"

class TileSelectionManager : public IActionManager
{
  public:
    ActionCostValue select_tile(CreaturePtr creature);
    ActionCostValue select_tile(CreaturePtr creature, const Direction d);
    ActionCostValue select_tile_cancel(CreaturePtr creature);

  protected:
    friend class ActionManager;
    TileSelectionManager();

    ActionCostValue get_action_cost_value() const;
};
