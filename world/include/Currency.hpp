#pragma once
#include "Item.hpp"

class Currency : public Item
{
  public:
    Currency();
    ~Currency();

    bool additional_item_attributes_match(ItemPtr item) const override;
        
    Item* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

using CurrencyPtr = std::shared_ptr<Currency>;

