#pragma once
#include "Creature.hpp"
#include "IActionManager.hpp"

class PickupManager : public IActionManager
{
  public:
    ActionCostValue pick_up(CreaturePtr creature, ActionManager * const am);

  protected:
    // Try to pick up and merge into the inventory.  Returns true if the item was merged,
    // false if the item does not merge with any item currently in the inventory.
    bool pick_up_and_merge_into_inventory(CreaturePtr creature, ItemPtr item);
    
    void handle_world_map_pickup(CreaturePtr creature);
    void handle_empty_tile_pickup(CreaturePtr creature);
    void handle_pickup(CreaturePtr creature);

    ActionCostValue get_action_cost_value() const;
};
