#include "BasicFeature.hpp"
#include "Serialize.hpp"

using namespace std;

BasicFeature::BasicFeature(const Symbol& new_symbol)
: Feature(MaterialType::MATERIAL_TYPE_UNKNOWN, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol), colour(new_symbol.get_colour())
{
}

BasicFeature::BasicFeature(const Symbol& new_symbol, const MaterialType mat, const string& new_desc_sid)
: Feature(mat, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol), description_sid(new_desc_sid), colour(new_symbol.get_colour())
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
  equal = equal && (description_sid == bf.description_sid);
  equal = equal && (colour == bf.colour);

  return equal;
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

  Serialize::write_string(stream, description_sid);
  Serialize::write_enum(stream, colour);

  return true;
}

bool BasicFeature::deserialize(std::istream& stream)
{
  Feature::deserialize(stream);

  Serialize::read_string(stream, description_sid);
  Serialize::read_enum(stream, colour);

  return true;
}

#ifdef UNIT_TESTS
#include "unit_tests/BasicFeature_test.cpp"
#endif
