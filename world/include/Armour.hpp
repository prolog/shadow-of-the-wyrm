#pragma once
#include "Wearable.hpp"

class Armour : public Wearable
{
  public:
    Armour();
    ~Armour();

    Item* clone();

  private:
    virtual ClassIdentifier internal_class_identifier() const;
};

typedef boost::shared_ptr<Armour> ArmourPtr;
