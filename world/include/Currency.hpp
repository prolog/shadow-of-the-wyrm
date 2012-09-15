#pragma once
#include "Item.hpp"

class Currency : public Item
{
  public:
    Currency();
    ~Currency();
    
    Item* clone();
};

typedef boost::shared_ptr<Currency> CurrencyPtr;

