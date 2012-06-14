#pragma once
#include "CombatManager.hpp"
#include "Creature.hpp"
#include "Directions.hpp"
#include "IActionManager.hpp"
#include "ItemManager.hpp"
#include "MovementManager.hpp"

enum ItemAction
{
  ITEM_ACTION_EQUIP = 0,
  ITEM_ACTION_PICK_UP = 1,
  ITEM_ACTION_DROP = 2
};

class ActionManager : public IActionManager
{
  public:
    ActionManager();
    ~ActionManager();

    void version();
    void dump_character(CreaturePtr creature);
    bool search(CreaturePtr creature);
    bool move(CreaturePtr creature, const Direction d);
    bool attack(CreaturePtr creature, const Direction d);
    bool ascend(CreaturePtr creature);
    bool descend(CreaturePtr creature);

    // Pick up/drop check the map type before proceeding.
    bool pick_up(CreaturePtr creature);
    bool drop(CreaturePtr creature);
    void equipment(CreaturePtr creature);

    // Display the inventory.  Potentially, select an item.  ItemPtr is null if no item
    // was selected.
    ItemPtr inventory(CreaturePtr creature, Inventory& inv, const bool inventory_is_read_only);
    
    // Unlike pick up/drop, handle item has no checks.
    bool remove_item(CreaturePtr creature, const EquipmentWornLocation worn_location);
    void wear_or_remove_item(CreaturePtr creature, const EquipmentWornLocation worn_location);
    bool handle_item(CreaturePtr creature, const ItemAction, ItemPtr item, const EquipmentWornLocation loc = EQUIPMENT_WORN_NONE);

  protected:
    uint get_current_action_cost();

    CombatManager combat_manager;
    MovementManager movement_manager;
    ItemManager item_manager;
};
