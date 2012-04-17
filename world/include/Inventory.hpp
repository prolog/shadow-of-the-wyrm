#pragma once
#include <list>
#include "Item.hpp"

class Inventory
{
  public:
    Inventory();
    ~Inventory();
    
    bool add_front(ItemPtr new_item);
    bool add(ItemPtr new_item);
    bool remove(const std::string& id);
    bool clear();
    ItemPtr at(const uint index);
    ItemPtr get_from_id(const std::string& id);
    bool empty() const; // returns whether the internal list of items is empty or not.
    uint size() const;
    
    std::list<ItemPtr> get_items();
    
  protected:
    std::list<ItemPtr> items;
};
