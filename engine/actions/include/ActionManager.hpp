#pragma once
#include <list>
#include "CombatManager.hpp"
#include "Creature.hpp"
#include "Directions.hpp"
#include "IItemFilter.hpp"
#include "ISerializable.hpp"
#include "ItemManager.hpp"
#include "MovementAction.hpp"
#include "QuaffAction.hpp"
#include "RangedCombatAction.hpp"
#include "SelectTileTypes.hpp"
#include "TileSelectionAction.hpp"
#include "WeaponTypes.hpp"

enum struct ItemAction
{
  ITEM_ACTION_EQUIP = 0,
  ITEM_ACTION_PICK_UP = 1,
  ITEM_ACTION_DROP = 2
};

class ActionManager : public ISerializable
{
  public:
    ActionManager();
    ~ActionManager();
    bool operator==(const ActionManager& am) const;

    ActionCost version(CreaturePtr creature);
    ActionCost date_and_time(CreaturePtr creature);
    ActionCost display_character(CreaturePtr creature);
    ActionCost dump_character(CreaturePtr creature);
    ActionCost search(CreaturePtr creature);
    ActionCost move(CreaturePtr creature, const Direction d);
    ActionCost automatic_movement(CreaturePtr creature);
    ActionCost attack(CreaturePtr creature, const Direction d);
    ActionCost ascend(CreaturePtr creature);
    ActionCost descend(CreaturePtr creature);

    // Pick up/drop check the map type before proceeding.
    ActionCost pick_up(CreaturePtr creature);
    ActionCost drop(CreaturePtr creature);
    ActionCost equipment(CreaturePtr creature);

    // Display the inventory.  Potentially, select an item.  ItemPtr is null if no item
    // was selected.
    ItemPtr inventory(CreaturePtr creature, IInventoryPtr inv, const std::list<IItemFilterPtr>& base_display_filter_list, const std::list<IItemFilterPtr>& additional_filter_list, const bool inventory_is_read_only);
    
    // Miscellaneous actions
    ActionCost pray(CreaturePtr creature);
    ActionCost weapon_info(CreaturePtr creature, const WeaponStyle weapon_style);

    // Tile selection actions.  The function with just the CreaturePtr is the main entry point - the others are used
    // for processing directional commands, cancellation, etc.
    ActionCost select_tile(CreaturePtr creature); // Examines the tiles on the current map
    ActionCostValue select_tile(CreaturePtr creature, const Direction d, TileSelectionAction* const tsa);
    ActionCostValue select_tile(CreaturePtr creature, const SelectCreatureType sct, TileSelectionAction* const tsa);
    
    // Actions utilizing tile selection actions:
    ActionCost fire_missile(CreaturePtr creature, const bool skip_targetting /* true for NPCs */);

    // Unlike pick up/drop, handle item has no checks.
    ActionCostValue remove_item(CreaturePtr creature, const EquipmentWornLocation worn_location);
    ActionCostValue wear_or_remove_item(CreaturePtr creature, const EquipmentWornLocation worn_location);
    ActionCostValue handle_item(CreaturePtr creature, const ItemAction, ItemPtr item, const EquipmentWornLocation loc = EquipmentWornLocation::EQUIPMENT_WORN_NONE);
    
    // Use a potion
    ActionCost quaff(CreaturePtr creature);
    
    // Read a scroll, or spellbook
    ActionCost read(CreaturePtr creature);
    
    // Check the current amount of currency held
    ActionCost check_currency(CreaturePtr creature);

    // Eat something
    ActionCost eat(CreaturePtr creature);

    // Chat with another creature
    ActionCost chat(CreaturePtr creature);

    // 'a'pply/h'a'ndle a terrain feature
    ActionCost apply(CreaturePtr creature);

    // List the current in-game quests.
    ActionCost quest_list(CreaturePtr creature);

    // Clear the Lua state so that any script changes will be applied on
    // the next load.
    void reload_scripts_and_sids(); // generic version.
    ActionCost reload_scripts_and_sids(CreaturePtr creature); // creature's-command-version
    ActionCost run_script_command(CreaturePtr creature); // should only be available in debug mode!

    ActionCost cast_spell(CreaturePtr creature, const std::string& spell_id, const Direction d);

    ActionCost bestiary(CreaturePtr creature);
    ActionCost bestiary(CreaturePtr creature, const std::string& creature_search_text);

    // Evoke/zap a wand.
    ActionCost evoke(CreaturePtr creature);

    // Show a creature's (well, the player's) resistances and vulnerabilities.
    ActionCost show_resistances(CreaturePtr creature);
    ActionCost show_conducts(CreaturePtr creature);

    // Display the message buffer
    ActionCost latest_messages(CreaturePtr creature);

    // Kick in a particular direction
    ActionCost kick(CreaturePtr creature);

    // Offer a sacrifice
    ActionCost offer(CreaturePtr creature);

    // Skin a corpse - skins can be treated at tanneries to make armour.
    ActionCost skin(CreaturePtr creature);

    // Determine the player's piety.
    ActionCost piety(CreaturePtr creature);

    // Rest for a while.
    ActionCost rest(CreaturePtr creature);

    // Show help information.
    ActionCost help(CreaturePtr creature);

    // Level and experience information.
    ActionCost experience(CreaturePtr creature);

    // Saves the game.
    ActionCost save(CreaturePtr creature);

    // Quits the game.  Right now this just sets a boolean flag in the game loop to be false, so there will need to be
    // additional work done later to compensate for pending actions, etc.
    ActionCost quit(CreaturePtr creature);

    bool serialize(std::ostream& ostream) const override;
    bool deserialize(std::istream& istream);

    ActionCost get_action_cost(CreaturePtr creature, const ActionCostValue action_cost_value);

  protected:    
    CombatManager combat_manager;
    MovementAction movement_action;
    ItemManager item_manager;
    TileSelectionAction tile_selection_action;
    RangedCombatAction ranged_combat_action;
    QuaffAction quaff_action;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
