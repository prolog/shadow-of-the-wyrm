#pragma once
#include "Wearable.hpp"

class Amulet : public Wearable
{
  public:
    Amulet();
    ~Amulet();
    
    Item* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

using AmuletPtr = std::shared_ptr<Amulet>;
