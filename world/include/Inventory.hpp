#pragma once
#include <list>
#include "Item.hpp"

enum InventoryAdditionType
{
  INVENTORY_ADDITION_FRONT = 0,
  INVENTORY_ADDITION_BACK = 1
};

class Inventory
{
  public:
    Inventory();
    ~Inventory();
    
    bool add_front(ItemPtr new_item);
    bool add(ItemPtr new_item);
    
    // Attempt to merge the item.  If the item cannot be merged into the
    // inventory, add it either to the front or to the back, based on the
    // parameter provided.
    void merge_or_add(ItemPtr item, const InventoryAdditionType inv_add_loc);

    // Attempt to merge the item.  Return true if the item could be merged into an existing item
    // in the inventory, false otherwise.  When returning false, the item is not added to the inventory.
    bool merge(ItemPtr new_item);
    
    bool remove(const std::string& id);
    
    bool clear();
    
    ItemPtr at(const uint index);
    ItemPtr get_from_id(const std::string& id);
    
    bool empty() const; // returns whether the internal list of items is empty or not.
    
    uint size() const;
    
    bool has_item_type(const ItemType type) const;
    
    std::list<ItemPtr> get_items();
    const std::list<ItemPtr> get_items_const() const;
    
  protected:
    std::list<ItemPtr> items;
};
