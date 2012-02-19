#pragma once
#include "Item.hpp"

class MiscItem : public Item
{
  public:
    MiscItem();
    ~MiscItem();

    Item* clone();
};
