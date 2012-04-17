#pragma once
#include "Wearable.hpp"

class Ammunition : public Wearable
{
  public:
    Ammunition();
    ~Ammunition();
    
    Item* clone();
};

typedef boost::shared_ptr<Ammunition> AmmunitionPtr;
