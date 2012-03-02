#pragma once
#include "Item.hpp"

class Wand : public Item
{
  public:
    Wand();
    ~Wand();
    
    uchar get_symbol() const;
    Item* clone();
};

typedef boost::shared_ptr<Wand> WandPtr;
