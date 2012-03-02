#pragma once
#include "Wearable.hpp"

class Ring : public Wearable
{
  public:
    Ring();
    ~Ring();
    
    uchar get_symbol() const;
    Item* clone();    
};

typedef boost::shared_ptr<Ring> RingPtr;
