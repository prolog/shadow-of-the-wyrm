#pragma once
#include "Wearable.hpp"

class Armour : public Wearable
{
  public:
    Armour();
    ~Armour();

    uchar get_symbol() const;
    Item* clone();
};

typedef boost::shared_ptr<Armour> ArmourPtr;
