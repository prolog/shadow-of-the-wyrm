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

ClassIdentifier Book::internal_class_identifier() const
{
  return CLASS_ID_BOOK;
}

#ifdef UNIT_TESTS
#include "unit_tests/Book_test.cpp"
#endif

