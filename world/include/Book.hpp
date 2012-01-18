#pragma once
#include "Item.hpp"

class Book : public Item
{
  public:
    Book();
    ~Book();

  protected:
};

typedef boost::shared_ptr<Book> BookPtr;
