#include "ShimmerColours.hpp"
#include "Serialize.hpp"

using namespace std;

const int ShimmerColours::BASE_PCT_CHANCE_SHIMMER = 70;
const size_t ShimmerColours::PASSABLE_IDX = 0;
const size_t ShimmerColours::IMPASSABLE_IDX = 1;
const size_t ShimmerColours::FEATURE_IDX = 1;
const size_t ShimmerColours::SHIMMER_IDX = 2;
const size_t ShimmerColours::VALID_SIZE = 3;

ShimmerColours::ShimmerColours()
: colours({ Colour::COLOUR_UNDEFINED, Colour::COLOUR_UNDEFINED, Colour::COLOUR_UNDEFINED}), pct_chance_shimmer(0)
{
}

ShimmerColours::ShimmerColours(const std::vector<Colour>& sh_colours, const int new_pct_chance_shimmer)
: colours(sh_colours), pct_chance_shimmer(new_pct_chance_shimmer)
{
}

bool ShimmerColours::operator==(const ShimmerColours& sc) const
{
  bool result = true;

  result = result && (colours == sc.colours);
  result = result && (pct_chance_shimmer == sc.pct_chance_shimmer);

  return true;
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

int ShimmerColours::get_pct_chance_shimmer() const
{
  return pct_chance_shimmer;
}

vector<Colour> ShimmerColours::get_raw_colours() const
{
  return colours;
}

bool ShimmerColours::serialize(ostream& stream) const
{
  Serialize::write_colour_vector(stream, colours);
  Serialize::write_int(stream, pct_chance_shimmer);

  return true;
}

bool ShimmerColours::deserialize(istream& stream)
{
  colours.clear();

  Serialize::read_colour_vector(stream, colours);
  Serialize::read_int(stream, pct_chance_shimmer);

  return true;
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

ClassIdentifier ShimmerColours::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SHIMMER_COLOURS;
}

#ifdef UNIT_TESTS
#include "unit_tests/ShimmerColours_test.cpp"
#endif
