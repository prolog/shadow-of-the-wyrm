#include "BasicFeature.hpp"
#include "Serialize.hpp"

using namespace std;

BasicFeature::BasicFeature()
: Feature(MaterialType::MATERIAL_TYPE_UNKNOWN, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL), symbol('?'), colour(Colour::COLOUR_WHITE)
{
}

BasicFeature::BasicFeature(const MaterialType mat, const uchar new_symbol, const Colour new_colour, const string& new_desc_sid)
: Feature(mat, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL), symbol(new_symbol), colour(new_colour), description_sid(new_desc_sid)
{
}

Feature* BasicFeature::clone()
{
  return new BasicFeature(*this);
}

bool BasicFeature::operator==(const BasicFeature& bf) const
{
  bool equal = true;

  equal = Feature::operator==(bf);

  equal = equal && (symbol == bf.symbol);
  equal = equal && (colour == bf.colour);
  equal = equal && (description_sid == bf.description_sid);

  return equal;
}

void BasicFeature::set_symbol(const uchar new_symbol)
{
  symbol = new_symbol;
}

uchar BasicFeature::get_symbol() const
{
  return symbol;
}

void BasicFeature::set_colour(const Colour new_colour)
{
  colour = new_colour;
}

Colour BasicFeature::get_colour() const
{
  return colour;
}

void BasicFeature::set_description_sid(const string& new_desc_sid)
{
  description_sid = new_desc_sid;
}

string BasicFeature::get_description_sid() const
{
  return description_sid;
}

ClassIdentifier BasicFeature::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_BASIC_FEATURE;
}

bool BasicFeature::serialize(std::ostream& stream) const
{
  Feature::serialize(stream);

  Serialize::write_uchar(stream, symbol);
  Serialize::write_enum(stream, colour);
  Serialize::write_string(stream, description_sid);

  return true;
}

bool BasicFeature::deserialize(std::istream& stream)
{
  Feature::deserialize(stream);

  Serialize::read_uchar(stream, symbol);
  Serialize::read_enum(stream, colour);
  Serialize::read_string(stream, description_sid);

  return true;
}

#ifdef UNIT_TESTS
#include "unit_tests/BasicFeature_test.cpp"
#endif
