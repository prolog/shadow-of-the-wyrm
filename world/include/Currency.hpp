#pragma once
#include "Item.hpp"

class Currency : public Item
{
  public:
    Currency();
    ~Currency();

    void set_status(const ItemStatus new_status) override;
    void set_status_identified(const bool new_status) override;

    bool additional_item_attributes_match(ItemPtr item) const override;
    bool get_type_always_stacks() const override;
        
    Item* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

using CurrencyPtr = std::shared_ptr<Currency>;

