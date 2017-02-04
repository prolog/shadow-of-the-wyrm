#pragma once
#include "Item.hpp"

class Staff : public Item
{
  public:
    Staff();
    ~Staff();

    bool additional_item_attributes_match(ItemPtr item) const override;
        
    Item* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

using StaffPtr = std::shared_ptr<Staff>;
