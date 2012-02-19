#pragma once
#include "Consumable.hpp"

class Potion : public Consumable
{
  public:
    Potion();
    ~Potion();
};

typedef boost::shared_ptr<Potion> PotionPtr;
