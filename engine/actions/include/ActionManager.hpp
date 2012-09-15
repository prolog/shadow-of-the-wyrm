#pragma once
#include <list>
#include "CombatManager.hpp"
#include "Creature.hpp"
#include "Directions.hpp"
#include "IItemFilter.hpp"
#include "ItemManager.hpp"
#include "MovementManager.hpp"
#include "QuaffManager.hpp"
#include "RangedCombatActionManager.hpp"
#include "TileSelectionManager.hpp"
#include "WeaponTypes.hpp"

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
    ActionCost date_and_time(CreaturePtr creature);
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
    ItemPtr inventory(CreaturePtr creature, Inventory& inv, const std::list<IItemFilterPtr>& display_filter_list, const bool inventory_is_read_only);
    
    // Miscellaneous actions
    ActionCost pray(CreaturePtr creature);
    ActionCost weapon_info(CreaturePtr creature, const WeaponStyle weapon_style);

    // Tile selection actions.  The function with just the CreaturePtr is the main entry point - the others are used
    // for processing directional commands, cancellation, etc.
    ActionCost select_tile(CreaturePtr creature); // Examines the tiles on the current map
    ActionCostValue select_tile(CreaturePtr creature, const Direction d, TileSelectionManager* const tsm);
    
    // Actions utilizing tile selection actions:
    ActionCost fire_missile(CreaturePtr creature);

    // Unlike pick up/drop, handle item has no checks.
    ActionCostValue remove_item(CreaturePtr creature, const EquipmentWornLocation worn_location);
    ActionCostValue wear_or_remove_item(CreaturePtr creature, const EquipmentWornLocation worn_location);
    ActionCostValue handle_item(CreaturePtr creature, const ItemAction, ItemPtr item, const EquipmentWornLocation loc = EQUIPMENT_WORN_NONE);
    
    // Use a potion
    ActionCost quaff(CreaturePtr creature);
    
    // Read a scroll, or spellbook
    ActionCost read(CreaturePtr creature);
    
    // Check the current amount of currency held
    ActionCost check_currency(CreaturePtr creature);

    // Quits the game.  Right now this just sets a boolean flag in the game loop to be false, so there will need to be
    // additional work done later to compensate for pending actions, etc.
    ActionCost quit(CreaturePtr creature);
    
  protected:
    ActionCost get_action_cost(CreaturePtr creature, const ActionCostValue action_cost_value);
    
    CombatManager combat_manager;
    MovementManager movement_manager;
    ItemManager item_manager;
    TileSelectionManager tile_selection_manager;
    RangedCombatActionManager ranged_combat_manager;
    QuaffManager quaff_manager;
};
