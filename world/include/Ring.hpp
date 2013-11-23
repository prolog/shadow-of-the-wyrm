#pragma once
#include "Wearable.hpp"

class Ring : public Wearable
{
  public:
    Ring();
    ~Ring();
    
    Item* clone();  

  private:
    ClassIdentifier internal_class_identifier() const;
};

typedef std::shared_ptr<Ring> RingPtr;
