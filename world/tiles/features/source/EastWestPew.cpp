#include "EastWestPew.hpp"

EastWestPew::EastWestPew(const Symbol& new_symbol)
: Pew(new_symbol)
{
}

Feature* EastWestPew::clone()
{
  return new EastWestPew(*this);
}

ClassIdentifier EastWestPew::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_EAST_WEST_PEW;
}

#ifdef UNIT_TESTS
#include "unit_tests/EastWestPew_test.cpp"
#endif

