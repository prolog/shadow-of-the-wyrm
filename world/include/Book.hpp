#pragma once
#include "Item.hpp"

class Book : public Item
{
  public:
    Book();
    ~Book();
    
    uchar get_symbol() const;
    Item* clone();
};

typedef boost::shared_ptr<Book> BookPtr;
