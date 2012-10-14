#include "EastWestPew.hpp"

EastWestPew::EastWestPew()
: Pew()
{
}

// Because the pews face east/west, a nicer symbol is needed for ASCII
// displays.
uchar EastWestPew::get_symbol() const
{
  return '|';
}

ClassIdentifier EastWestPew::internal_class_identifier() const
{
  return CLASS_ID_EAST_WEST_PEW;
}