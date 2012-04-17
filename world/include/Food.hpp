#pragma once
#include <boost/shared_ptr.hpp>
#include "Consumable.hpp"

class Food : public Consumable
{
  public:
    Food();
    Food(const int nutr);
    ~Food();

    ItemType get_type() const;
    
    Item* clone();
};

typedef boost::shared_ptr<Food> FoodPtr;
