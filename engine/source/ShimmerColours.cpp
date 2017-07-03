#include "ShimmerColours.hpp"

using namespace std;

const size_t ShimmerColours::PASSABLE_IDX = 0;
const size_t ShimmerColours::IMPASSABLE_IDX = 1;
const size_t ShimmerColours::FEATURE_IDX = 1;
const size_t ShimmerColours::SHIMMER_IDX = 2;
const size_t ShimmerColours::VALID_SIZE = 3;

ShimmerColours::ShimmerColours(const std::vector<Colour>& sh_colours)
: colours(sh_colours)
{
}

Colour ShimmerColours::get_passable_colour() const
{
  return get_colour_or_undefined(PASSABLE_IDX);
}

Colour ShimmerColours::get_impassable_colour() const
{
  return get_colour_or_undefined(IMPASSABLE_IDX);
}

Colour ShimmerColours::get_feature_colour() const
{
  return get_colour_or_undefined(FEATURE_IDX);
}

Colour ShimmerColours::get_shimmer_colour() const
{
  return get_colour_or_undefined(SHIMMER_IDX);
}

Colour ShimmerColours::get_colour_or_undefined(const size_t idx) const
{
  Colour colour = Colour::COLOUR_UNDEFINED;

  if (is_valid() && idx < colours.size())
  {
    colour = colours.at(idx);
  }

  return colour;
}

bool ShimmerColours::is_valid() const
{
  return colours.size() == VALID_SIZE;
}

#ifdef UNIT_TESTS
#include "unit_tests/ShimmerColours_test.cpp"
#endif
