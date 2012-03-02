#pragma once
#include "Wearable.hpp"

class Amulet : public Wearable
{
  public:
    Amulet();
    ~Amulet();
    
    uchar get_symbol() const;
    Item* clone();
};

typedef boost::shared_ptr<Amulet> AmuletPtr;
