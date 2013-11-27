#pragma once
#include "Item.hpp"

class Boat : public Item
{
  public:
    Boat();
    ~Boat();
    
    Item* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

typedef std::shared_ptr<Boat> BoatPtr;
