#pragma once
#include "Wearable.hpp"

class Ring : public Wearable
{
  public:
    Ring();
    ~Ring();
    
    ItemType get_type() const;

  protected:
};

typedef boost::shared_ptr<Ring> RingPtr;
