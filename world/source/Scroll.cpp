#include "Scroll.hpp"

using namespace std;

Scroll::Scroll()
{
  type = ITEM_TYPE_SCROLL;
  symbol = '?';
}

Scroll::~Scroll()
{
}

// Scrolls are always gone once read.
bool Scroll::destroy_on_read() const
{
  return true;
}

Item* Scroll::clone()
{
  return new Scroll(*this);
}

ClassIdentifier Scroll::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SCROLL;
}

#ifdef UNIT_TESTS
#include "unit_tests/Scroll_test.cpp"
#endif

