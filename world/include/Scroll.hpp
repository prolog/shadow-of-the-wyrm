#pragma once
#include "Item.hpp"

class Scroll : public Item
{
  public:
    Scroll();
    ~Scroll();
    
    Item* clone();
};

typedef boost::shared_ptr<Scroll> ScrollPtr;
