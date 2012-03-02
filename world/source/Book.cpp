#include "Book.hpp"

Book::Book()
{
  type = ITEM_TYPE_BOOK;
}

Book::~Book()
{
}

uchar Book::get_symbol() const
{
  return '\"';
}

Item* Book::clone()
{
  return new Book(*this);
}
