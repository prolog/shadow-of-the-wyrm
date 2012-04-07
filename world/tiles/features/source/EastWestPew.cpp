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
