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

    Item* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

using FoodPtr = std::shared_ptr<Food>;
