#pragma once
#include "CombatManager.hpp"
#include "Creature.hpp"
#include "Directions.hpp"
#include "ItemManager.hpp"
#include "MovementManager.hpp"

enum ItemAction
{
  ITEM_ACTION_EQUIP = 0,
  ITEM_ACTION_PICK_UP = 1,
  ITEM_ACTION_DROP = 2
};

class ActionManager
{
  public:
    ActionManager();
    ~ActionManager();

    ActionCost version(CreaturePtr creature);
    ActionCost dump_character(CreaturePtr creature);
    ActionCost search(CreaturePtr creature);
    ActionCost move(CreaturePtr creature, const Direction d);
    ActionCost attack(CreaturePtr creature, const Direction d);
    ActionCost ascend(CreaturePtr creature);
    ActionCost descend(CreaturePtr creature);

    // Pick up/drop check the map type before proceeding.
    ActionCost pick_up(CreaturePtr creature);
    ActionCost drop(CreaturePtr creature);
    ActionCost equipment(CreaturePtr creature);

    // Display the inventory.  Potentially, select an item.  ItemPtr is null if no item
    // was selected.
    ItemPtr inventory(CreaturePtr creature, Inventory& inv, const bool inventory_is_read_only);
    
    // Unlike pick up/drop, handle item has no checks.
    ActionCostValue remove_item(CreaturePtr creature, const EquipmentWornLocation worn_location);
    void wear_or_remove_item(CreaturePtr creature, const EquipmentWornLocation worn_location);
    ActionCostValue handle_item(CreaturePtr creature, const ItemAction, ItemPtr item, const EquipmentWornLocation loc = EQUIPMENT_WORN_NONE);

    // Quits the game.  Right now this just sets a boolean flag in the game loop to be false, so there will need to be
    // additional work done later to compensate for pending actions, etc.
    ActionCost quit(CreaturePtr creature);
    
  protected:
    ActionCost get_action_cost(CreaturePtr creature, const ActionCostValue action_cost_value);
    
    CombatManager combat_manager;
    MovementManager movement_manager;
    ItemManager item_manager;
};
