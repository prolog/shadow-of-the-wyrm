#pragma once
#include <boost/shared_ptr.hpp>
#include "Consumable.hpp"

class Plant : public Consumable
{
  public:
    Plant();
    Plant(const int new_nutrition);
    ~Plant();

    ItemType get_type() const;

    Item* clone();
};

typedef boost::shared_ptr<Plant> PlantPtr;
