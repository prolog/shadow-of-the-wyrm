#pragma once
#include "Item.hpp"

class Currency : public Item
{
  public:
    Currency();
    ~Currency();
    
    Item* clone();

  private:
    ClassIdentifier internal_class_identifier() const;
};

typedef std::shared_ptr<Currency> CurrencyPtr;

