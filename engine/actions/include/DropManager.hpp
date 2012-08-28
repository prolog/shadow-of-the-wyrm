#pragma once
#include "IActionManager.hpp"

class ActionManager;

class DropManager : public IActionManager
{
  public:
    ActionCostValue drop(CreaturePtr creature, ActionManager * const am);
    
  protected:
    void handle_world_drop(CreaturePtr creature);
    void handle_item_dropped_message(CreaturePtr creature, ItemPtr item);
    void handle_no_item_dropped(CreaturePtr creature);
    void handle_invalid_drop_quantity(CreaturePtr creature);
    
    ActionCostValue do_drop(CreaturePtr creature, MapPtr current_map, ItemPtr item);

    ActionCostValue get_action_cost_value() const;
};
