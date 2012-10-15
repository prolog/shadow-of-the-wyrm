#pragma once
#include "Consumable.hpp"

class Potion : public Consumable
{
  public:
    Potion();
    ~Potion();
    
    ItemType get_type() const;
    Item* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

typedef boost::shared_ptr<Potion> PotionPtr;
