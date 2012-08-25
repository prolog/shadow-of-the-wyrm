#pragma once
#include "Creature.hpp"
#include "IActionManager.hpp"

class PickupManager : public IActionManager
{
  public:
    ActionCostValue pick_up(CreaturePtr creature, ActionManager * const am);

  protected:
    void handle_world_map_pickup(CreaturePtr creature);
    void handle_empty_tile_pickup(CreaturePtr creature);
    void handle_pickup(CreaturePtr creature);

    ActionCostValue get_action_cost_value() const;
};
