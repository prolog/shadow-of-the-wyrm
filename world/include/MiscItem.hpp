#pragma once
#include "Item.hpp"

class MiscItem : public Item
{
  public:
    MiscItem();
    ~MiscItem();

    uchar get_symbol() const;
    Item* clone();
};
