#include "ColourUtils.hpp"

const int ColourUtils::COLOUR_BOLD_OFFSET = 8;

ColourUtils::ColourUtils()
{
}

ColourUtils::~ColourUtils()
{
}

Colour ColourUtils::get_alternate_hue(const Colour c)
{
  Colour new_hue = c;

  if (c > Colour::COLOUR_UNDEFINED && c < Colour::COLOUR_BOLD_BLACK)
  {
    new_hue = static_cast<Colour>(static_cast<int>(c) + COLOUR_BOLD_OFFSET);
  }
  else
  {
    new_hue = static_cast<Colour>(static_cast<int>(c) - COLOUR_BOLD_OFFSET);
  }

  return new_hue;
}

#ifdef UNIT_TESTS
#include "unit_tests/ColourUtils_test.cpp"
#endif
