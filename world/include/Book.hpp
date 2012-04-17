#pragma once
#include "Item.hpp"

class Book : public Item
{
  public:
    Book();
    ~Book();
    
    Item* clone();
};

typedef boost::shared_ptr<Book> BookPtr;
