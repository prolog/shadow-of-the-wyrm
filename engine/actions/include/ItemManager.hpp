#pragma once
#include "Creature.hpp"
#include "IActionManager.hpp"
#include "Item.hpp"

class ItemManager : public IActionManager
{
  public:
    // Create a new item from a given item.  This is used to make copies of the
    // template items, so that, say, fifty distinct broadswords can be created.
    ItemPtr create_item(const ItemMap& items, const std::string& item_id, const uint quantity);
    
    static ItemPtr create_item(const std::string& item_id, const uint quantity = 1); // This version assumes that we use the collection on the Game singleton.
    static void create_item_with_probability(const int rand_less_than_or_equal_val, const int rand_upper_bound, Inventory& inv, const std::string& item_id);

    ActionCostValue pick_up(CreaturePtr creature, ItemPtr item);
    ActionCostValue drop(CreaturePtr creature, ItemPtr item);
    ActionCostValue equip(CreaturePtr creature, ItemPtr item, const EquipmentWornLocation location);
    ActionCostValue equip(CreaturePtr creature, ItemPtr item);
    ItemPtr remove(CreaturePtr creature, const EquipmentWornLocation location, bool transfer_to_inventory = true);
    
  protected:
    friend class ActionManager;
    friend class RangedCombatActionManager;
    
    ItemManager();
    ~ItemManager();
    
    ActionCostValue equip_and_remove_from_inventory(CreaturePtr creature, ItemPtr item, const EquipmentWornLocation eq_worn_slot);
    ActionCostValue equip_and_reduce_inventory_quantity(CreaturePtr creature, ItemPtr item, const EquipmentWornLocation eq_worn_slot, const uint quantity);

    ActionCostValue get_action_cost_value() const;

};
