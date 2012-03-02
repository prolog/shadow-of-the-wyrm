#pragma once
#include "Wearable.hpp"

class Ammunition : public Wearable
{
  public:
    Ammunition();
    ~Ammunition();
    
    uchar get_symbol() const;
    Item* clone();
};

typedef boost::shared_ptr<Ammunition> AmmunitionPtr;
