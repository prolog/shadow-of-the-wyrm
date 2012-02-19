#pragma once
#include "Item.hpp"

class ItemFactory
{
  public:
    static ItemPtr create(ItemPtr item_to_clone);

  protected:
    ItemFactory();
    ~ItemFactory();
};
