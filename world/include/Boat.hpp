#pragma once
#include "Item.hpp"

class Boat : public Item
{
  public:
    Boat();
    ~Boat();
    
    Item* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

typedef std::shared_ptr<Boat> BoatPtr;
