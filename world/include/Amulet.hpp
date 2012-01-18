#pragma once
#include "Wearable.hpp"

class Amulet : public Wearable
{
  public:
    Amulet();
    ~Amulet();
    
    ItemType get_type() const;

  protected:
};

typedef boost::shared_ptr<Amulet> AmuletPtr;
