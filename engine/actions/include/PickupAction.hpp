#pragma once
#include "Creature.hpp"
#include "IActionManager.hpp"

class PickupAction : public IActionManager
{
  public:
    ActionCostValue pick_up(CreaturePtr creature, ActionManager * const am);

    bool merge_into_equipment(CreaturePtr creature, ItemPtr item);
    bool merge_or_add_into_inventory(CreaturePtr creature, ItemPtr item);

  protected:
    void handle_world_map_pickup(CreaturePtr creature);
    void handle_empty_tile_pickup(CreaturePtr creature);
    ActionCostValue handle_pickup(CreaturePtr creature, MapPtr map, ActionManager * const am);
    
    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;
};
