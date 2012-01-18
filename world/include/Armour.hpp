#pragma once
#include "Wearable.hpp"

class Armour : public Wearable
{
  public:
    Armour();
    ~Armour();

    virtual ItemType get_type() const;

  protected:
};

typedef boost::shared_ptr<Armour> ArmourPtr;
