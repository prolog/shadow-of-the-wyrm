#include "EastWestPew.hpp"

EastWestPew::EastWestPew()
: Pew()
{
}

Feature* EastWestPew::clone()
{
  return new EastWestPew(*this);
}

// Because the pews face east/west, a nicer symbol is needed for ASCII
// displays.
uchar EastWestPew::get_symbol() const
{
  return '|';
}

ClassIdentifier EastWestPew::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_EAST_WEST_PEW;
}

#ifdef UNIT_TESTS
#include "unit_tests/EastWestPew_test.cpp"
#endif

