#pragma once
#include <memory>
#include <list>
#include "Item.hpp"
#include "ISerializable.hpp"

enum InventoryAdditionType
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

    virtual bool add_front(ItemPtr new_item) = 0;
    virtual bool add(ItemPtr new_item) = 0;

    // Attempt to merge the item.  If the item cannot be merged into the
    // inventory, add it either to the front or to the back, based on the
    // parameter provided.
    virtual void merge_or_add(ItemPtr item, const InventoryAdditionType inv_add_loc) = 0;

    // Attempt to merge the item.  Return true if the item could be merged into an existing item
    // in the inventory, false otherwise.  When returning false, the item is not added to the inventory.
    virtual bool merge(ItemPtr new_item) = 0;

    virtual bool remove(const std::string& id) = 0;
    virtual bool remove_by_base_id(const std::string& base_id) = 0;

    virtual bool clear() = 0;

    virtual bool has_items() const = 0;
    virtual ItemPtr at(const uint index) = 0;
    virtual ItemPtr get_from_id(const std::string& id) = 0;
    virtual ItemPtr get_from_base_id(const std::string& base_id) = 0;

    virtual bool empty() const = 0; // returns whether the internal list of items is empty or not.

    virtual uint size() const = 0;

    virtual bool has_item_type(const ItemType type) const = 0;
    virtual bool has_item_with_property(const std::string& additional_property_name) const = 0;
    virtual int count_items_with_property(const std::string& additional_property_name) const = 0;

    virtual std::list<ItemPtr>& get_items_ref() = 0;
    virtual const std::list<ItemPtr>& get_items_cref() const = 0;

    virtual bool serialize(std::ostream& stream) const override = 0;
    virtual bool deserialize(std::istream& stream) override = 0;

  private:
    virtual ClassIdentifier internal_class_identifier() const override = 0;
};

typedef std::shared_ptr<IInventory> IInventoryPtr;