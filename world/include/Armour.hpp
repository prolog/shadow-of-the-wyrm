#pragma once
#include "Wearable.hpp"

class Armour : public Wearable
{
  public:
    Armour();
    ~Armour();

    Item* clone();
};

typedef boost::shared_ptr<Armour> ArmourPtr;
