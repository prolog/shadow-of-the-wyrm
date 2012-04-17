#pragma once
#include "Item.hpp"

class Wand : public Item
{
  public:
    Wand();
    ~Wand();
    
    Item* clone();
};

typedef boost::shared_ptr<Wand> WandPtr;
