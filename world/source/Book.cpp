#include "Book.hpp"

Book::Book()
{
  type = ITEM_TYPE_BOOK;
  symbol = '\"';
}

Book::~Book()
{
}

bool Book::destroy_on_read() const
{
  return false;
}

Item* Book::clone()
{
  return new Book(*this);
}
