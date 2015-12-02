#pragma once
#include <memory>
#include "Consumable.hpp"

class Food : public Consumable
{
  public:
    Food();
    Food(const int nutr);
    ~Food();

    ItemType get_type() const override;

    // If this is a piece of fruit, or something similar, it can have
    // seeds, a pit, etc.  This is represented by the seed item id on
    // the item, and is used to create a follow-up item after the food
    // has been eaten.
    void set_seed_item_id(const std::string& new_seed_item_id);
    std::string get_seed_item_id() const;

    Item* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

using FoodPtr = std::shared_ptr<Food>;
