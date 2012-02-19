#pragma once
#include "Wearable.hpp"

class Ring : public Wearable
{
  public:
    Ring();
    ~Ring();
};

typedef boost::shared_ptr<Ring> RingPtr;
