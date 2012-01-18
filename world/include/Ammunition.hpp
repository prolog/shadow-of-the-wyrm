#pragma once
#include "Wearable.hpp"

class Ammunition : public Wearable
{
  public:
    Ammunition();
    ~Ammunition();

    ItemType get_type() const;
};

typedef boost::shared_ptr<Ammunition> AmmunitionPtr;
