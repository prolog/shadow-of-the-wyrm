#pragma once
#include <list>
#include "Item.hpp"

class Inventory
{
  public:
    Inventory();
    ~Inventory();
    
  protected:
    std::list<ItemPtr> items;
};
