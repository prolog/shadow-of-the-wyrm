#pragma once
#include <map>
#include <memory>
#include <list>
#include <vector>
#include "Item.hpp"
#include "ISerializable.hpp"

enum struct InventoryAdditionType
{
  INVENTORY_ADDITION_FRONT = 0,
  INVENTORY_ADDITION_BACK = 1
};

// Interface for Inventory classes.  Implementing classes are:
//
// - Inventory (a regular inventory, used almost everywhere)
// - NullInventory (an inventory that always contains nothing -
//   used by tiles that do not support dropping items, and
//   potentially in other cases too).
class IInventory : public ISerializable
{
  public:
    virtual bool operator==(const IInventory& inv) const = 0;

    // Mark that the inventory needs to be restacked.
    virtual void mark_for_restack() = 0;
    virtual bool get_marked_for_restack() const = 0;

    virtual bool get_allows_items() const = 0;
    virtual bool add_front(ItemPtr new_item) = 0;
    virtual bool add(ItemPtr new_item) = 0;

    // Attempt to merge the item.  If the item cannot be merged into the
    // inventory, add it either to the front or to the back, based on the
    // parameter provided.
    virtual bool merge_or_add(ItemPtr item, const InventoryAdditionType inv_add_loc) = 0;

    // Attempt to merge the item.  Return true if the item could be merged into an existing item
    // in the inventory, false otherwise.  When returning false, the item is not added to the inventory.
    virtual bool merge(ItemPtr new_item) = 0;

    virtual bool remove(const std::string& id) = 0;
    virtual ItemPtr remove_and_return(const std::string& id) = 0;
    virtual std::pair<bool, std::vector<ItemPtr>> remove_by_base_id(const std::string& base_id, const int quantity = 1, const std::map<std::string, std::string>& properties = {}) = 0;

    virtual bool clear() = 0;

    // Set a property on all items in the inventory.
    virtual void set_additional_property(const std::string& property_name, const std::string& property_value) = 0;

    virtual bool has_items() const = 0;
    virtual bool has_unpaid_items() const = 0;
    virtual bool has_item(const std::string& base_id) const = 0;

    virtual ItemPtr at(const uint index) = 0;
    virtual ItemPtr get_from_id(const std::string& id) = 0;
    virtual std::vector<ItemPtr> get_all_from_base_id(const std::string& id) = 0;
    virtual std::vector<ItemPtr> get_all_from_property(const std::string& property_name) = 0;
    virtual std::vector<ItemPtr> get_all_from_property(const std::string& property_name, const std::string& required_value) = 0;
    virtual ItemPtr get_from_base_id(const std::string& base_id) = 0;
    virtual std::vector<ItemPtr> get_from_type(const ItemType item_type) = 0;

    virtual bool empty() const = 0; // returns whether the internal list of items is empty or not.

    virtual uint size() const = 0;

    virtual bool has_item_type(const ItemType type) const = 0;
    virtual bool has_item_with_property(const std::string& additional_property_name) const = 0;
    virtual uint count_items_with_property(const std::string& additional_property_name) const = 0;
    virtual uint count_items_without_property(const std::string& additional_property_name) const = 0;
    virtual uint count_items(const std::string& item_base_id) const = 0;
    virtual uint count_items() const = 0;
    virtual uint count_currency() const = 0;

    virtual void set_items(const std::list<ItemPtr>& items) = 0;
    virtual void add_items(const std::list<ItemPtr>& items) = 0;
    virtual std::list<ItemPtr>& get_items_ref() = 0;
    virtual const std::list<ItemPtr>& get_items_cref() const = 0;

    virtual std::string get_drop_effect_sid() const = 0;

    virtual bool serialize(std::ostream& stream) const override = 0;
    virtual bool deserialize(std::istream& stream) override = 0;

  private:
    virtual ClassIdentifier internal_class_identifier() const override = 0;
};

using IInventoryPtr = std::shared_ptr<IInventory>;