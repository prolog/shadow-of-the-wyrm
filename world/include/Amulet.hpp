#pragma once
#include "Wearable.hpp"

class Amulet : public Wearable
{
  public:
    Amulet();
    ~Amulet();
};

typedef boost::shared_ptr<Amulet> AmuletPtr;
