#pragma once
#include <memory>
#include "Consumable.hpp"

class Plant : public Consumable
{
  public:
    Plant();
    Plant(const int new_nutrition);
    ~Plant();

    ItemType get_type() const override;

    Item* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

typedef std::shared_ptr<Plant> PlantPtr;
