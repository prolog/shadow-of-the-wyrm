#pragma once
#include "Item.hpp"

class Boat : public Item
{
  public:
    Boat();
    ~Boat();
    
    Item* clone();
};

typedef boost::shared_ptr<Boat> BoatPtr;
