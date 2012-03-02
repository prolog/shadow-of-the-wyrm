#pragma once
#include "Item.hpp"

class Scroll : public Item
{
  public:
    Scroll();
    ~Scroll();
    
    uchar get_symbol() const;
    Item* clone();
};

typedef boost::shared_ptr<Scroll> ScrollPtr;
