#pragma once
#include <list>
#include "Item.hpp"

class Inventory
{
  public:
    Inventory();
    ~Inventory();
    
    bool add(ItemPtr new_item);
    bool remove(ItemPtr item);
    
    std::list<ItemPtr> get_items();
    
  protected:
    std::list<ItemPtr> items;
};
