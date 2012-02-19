#pragma once
#include "Item.hpp"

class Book : public Item
{
  public:
    Book();
    ~Book();
};

typedef boost::shared_ptr<Book> BookPtr;
