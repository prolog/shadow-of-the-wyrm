#pragma once
#include "Consumable.hpp"

class Potion : public Consumable
{
  public:
    Potion();
    ~Potion();
    
    ItemType get_type() const;
    uchar get_symbol() const;
    Item* clone();
};

typedef boost::shared_ptr<Potion> PotionPtr;
