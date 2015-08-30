#pragma once
#include "Wearable.hpp"

class Armour : public Wearable
{
  public:
    Armour();
    ~Armour();

    Item* clone() override;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

using ArmourPtr = std::shared_ptr<Armour>;
