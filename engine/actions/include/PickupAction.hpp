#pragma once
#include "Creature.hpp"
#include "IActionManager.hpp"

class ActionManager;

enum struct PickUpType
{
  PICK_UP_SINGLE = 0,
  PICK_UP_ALL = 1
};

class PickupAction : public IActionManager
{
  public:
    ActionCostValue pick_up(CreaturePtr creature, ActionManager * const am, const PickUpType pick_up);
    ActionCostValue toggle_autopickup(CreaturePtr creature);

    bool merge_into_equipment(CreaturePtr creature, ItemPtr item);
    bool merge_or_add_into_inventory(CreaturePtr creature, ItemPtr item);

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:
    void handle_world_map_pickup(CreaturePtr creature);
    void handle_empty_tile_pickup(CreaturePtr creature);
    void handle_cannot_pickup(CreaturePtr creature, const std::string& msg_sid);
    void potentially_identify_status(CreaturePtr creature, ItemPtr item);

    ActionCostValue handle_pickup(CreaturePtr creature, MapPtr map, ActionManager * const am, const PickUpType pick_up);    
    ActionCostValue handle_pickup_single(CreaturePtr creature, MapPtr map, ActionManager * const am, TilePtr tile);
    ActionCostValue handle_pickup_all(CreaturePtr creature, MapPtr map, ActionManager * const am, TilePtr tile);
    void take_item_and_give_to_creature(ItemPtr item, IInventoryPtr inv, CreaturePtr creature);
};
