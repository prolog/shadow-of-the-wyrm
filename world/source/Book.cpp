#include "Book.hpp"

Book::Book()
{
  type = ITEM_TYPE_BOOK;
  symbol = '\"';
}

Book::~Book()
{
}

Item* Book::clone()
{
  return new Book(*this);
}
