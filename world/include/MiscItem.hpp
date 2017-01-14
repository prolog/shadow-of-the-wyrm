#pragma once
#include "Item.hpp"

class MiscItem : public Item
{
  public:
    MiscItem();
    ~MiscItem();

    bool additional_item_attributes_match(ItemPtr item) const override;

    Item* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
