#pragma once
#include "Wearable.hpp"

class Ring : public Wearable
{
  public:
    Ring();
    ~Ring();
    
    Item* clone();    
};

typedef boost::shared_ptr<Ring> RingPtr;
