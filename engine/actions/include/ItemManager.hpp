#pragma once
#include <map>
#include "Creature.hpp"
#include "IActionManager.hpp"
#include "Item.hpp"
#include "IItemFilter.hpp"

class ItemManager : public IActionManager
{
  public:
    bool operator==(const ItemManager& im) const;

    // Get all items by a particular type
    static std::list<ItemPtr> get_items_by_type(CreaturePtr creature, const ItemType item_type); // both eq and inv are checked in this case.
    static std::list<ItemPtr> get_items_by_type(const IInventoryPtr inv, const ItemType item_type); // Only the given inventory is checked.
    static std::list<ItemPtr> get_items_by_type(const Equipment& eq, const ItemType item_type); // Only the given equipment is checked.
    static std::list<ItemPtr> get_filtered_items(const IInventoryPtr inv, const std::list<IItemFilterPtr>& item_filters); // get items that pass a particular set of filters

                                                                                                 // Check to see if an item exists, given the base ID.
    static bool has_item(CreaturePtr creature, const std::string& base_item_id, const std::map<std::string, std::string>& properties = {});

    // Create a new item from a given item.  This is used to make copies of the
    // template items, so that, say, fifty distinct broadswords can be created.
    static ItemPtr create_item(const ItemMap& items, const std::string& item_id, const uint quantity);

    // Remove an item by base ID, first checking the creature's equipment, and then
    // the inventory.  Return true if an item with the given ID was removed, or the
    // quantity reduced by 1, and also return the vector of items.
    std::pair<bool, std::vector<ItemPtr>> remove_item_from_inv_or_eq(CreaturePtr creature, const std::string& base_item_id, const int quantity = 1, const std::map<std::string, std::string>& properties = {});
    
    static ItemPtr create_item(const std::string& item_id, const uint quantity = 1); // This version assumes that we use the collection on the Game singleton.
    static bool create_item_with_probability(const int rand_less_than_or_equal_val, const int rand_upper_bound, IInventoryPtr inv, const std::string& item_id, const uint quantity = 1, const bool disallow_cursed = false);

    ActionCostValue pick_up(CreaturePtr creature, ItemPtr item);
    ActionCostValue drop(CreaturePtr creature, ItemPtr item);
    ActionCostValue equip(CreaturePtr creature, ItemPtr item, const EquipmentWornLocation location);
    ActionCostValue equip(CreaturePtr creature, ItemPtr item);
    ItemPtr remove(CreaturePtr creature, const EquipmentWornLocation location, bool transfer_to_inventory = true);

    ActionCostValue get_action_cost_value(CreaturePtr creature) const override;

  protected:    
    ActionCostValue equip_and_remove_from_inventory(CreaturePtr creature, ItemPtr item, const EquipmentWornLocation eq_worn_slot);
    ActionCostValue equip_and_reduce_inventory_quantity(CreaturePtr creature, ItemPtr item, const EquipmentWornLocation eq_worn_slot, const uint quantity);
    void handle_item_identification_and_statuses(CreaturePtr creature, ItemPtr item);
};
