#pragma once
#include "Item.hpp"

class Boat : public Item
{
  public:
    Boat();
    ~Boat();

    bool additional_item_attributes_match(ItemPtr item) const override;
    
    Item* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

using BoatPtr = std::shared_ptr<Boat>;
