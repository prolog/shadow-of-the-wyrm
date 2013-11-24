#pragma once
#include "Item.hpp"

class MiscItem : public Item
{
  public:
    MiscItem();
    ~MiscItem();

    Item* clone();

  private:
    ClassIdentifier internal_class_identifier() const override;
};
