#pragma once
#include "IActionManager.hpp"

class TileSelectionManager : public IActionManager
{
  public:
    ActionCostValue select_tile(CreaturePtr creature);
    ActionCostValue select_tile(CreaturePtr creature, const Direction d);

  protected:
    friend class ActionManager;
    TileSelectionManager();

    ActionCostValue get_action_cost_value() const;
};
