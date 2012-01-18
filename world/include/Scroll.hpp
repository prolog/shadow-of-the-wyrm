#pragma once
#include "Item.hpp"

class Scroll : public Item
{
  public:
    Scroll();
    ~Scroll();
};

typedef boost::shared_ptr<Scroll> ScrollPtr;
