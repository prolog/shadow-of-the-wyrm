#include "ConfigurableFeature.hpp"
#include "Serialize.hpp"

using namespace std;

ConfigurableFeature::ConfigurableFeature(const Symbol& new_symbol)
: Feature("", MaterialType::MATERIAL_TYPE_UNKNOWN, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol), colour(new_symbol.get_colour())
{
}

ConfigurableFeature::ConfigurableFeature(const Symbol& new_symbol, const MaterialType mat, const string& new_desc_sid)
: Feature(new_desc_sid, mat, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol), description_sid(new_desc_sid), colour(new_symbol.get_colour())
{
}

Feature* ConfigurableFeature::clone()
{
  return new ConfigurableFeature(*this);
}

bool ConfigurableFeature::operator==(const ConfigurableFeature& cf) const
{
  bool equal = true;

  equal = Feature::operator==(cf);
  equal = equal && (description_sid == cf.description_sid);
  equal = equal && (colour == cf.colour);

  return equal;
}

void ConfigurableFeature::set_colour(const Colour new_colour)
{
  colour = new_colour;
}

Colour ConfigurableFeature::get_colour() const
{
  return colour;
}

void ConfigurableFeature::set_description_sid(const string& new_desc_sid)
{
  description_sid = new_desc_sid;
}

ClassIdentifier ConfigurableFeature::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_CONFIGURABLE_FEATURE;
}

bool ConfigurableFeature::serialize(std::ostream& stream) const
{
  Feature::serialize(stream);
  Serialize::write_enum(stream, colour);

  return true;
}

bool ConfigurableFeature::deserialize(std::istream& stream)
{
  Feature::deserialize(stream);
  Serialize::read_enum(stream, colour);

  return true;
}

#ifdef UNIT_TESTS
#include "unit_tests/ConfigurableFeature_test.cpp"
#endif
