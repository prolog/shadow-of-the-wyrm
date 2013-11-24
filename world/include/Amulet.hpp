#pragma once
#include "Wearable.hpp"

class Amulet : public Wearable
{
  public:
    Amulet();
    ~Amulet();
    
    Item* clone();

  private:
    ClassIdentifier internal_class_identifier() const override;
};

typedef std::shared_ptr<Amulet> AmuletPtr;
