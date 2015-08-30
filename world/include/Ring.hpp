#pragma once
#include "Wearable.hpp"

class Ring : public Wearable
{
  public:
    Ring();
    ~Ring();
    
    Item* clone() override;  

  private:
    ClassIdentifier internal_class_identifier() const override;
};

using RingPtr = std::shared_ptr<Ring>;
