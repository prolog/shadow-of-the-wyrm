#include "FeatureDescriptionTextKeys.hpp"
#include "MaterialFactory.hpp"
#include "Serialize.hpp"
#include "Sign.hpp"

using namespace std;

Sign::Sign(const Symbol& new_symbol, const string& new_text_sid)
: Feature(MaterialType::MATERIAL_TYPE_WOOD, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol), text_sid(new_text_sid)
{
}

bool Sign::operator==(const Sign& s) const
{
  bool result = Feature::operator==(s);
  result = result && (text_sid == s.text_sid);

  return result;
}

Feature* Sign::clone()
{
  return new Sign(*this);
}

string Sign::get_description_sid() const
{
  return text_sid;
}

pair<string, vector<string>> Sign::get_description_and_replacement_sids() const
{
  vector<string> replace = {get_description_sid()};
  return make_pair(FeatureDescriptionTextKeys::FEATURE_DESCRIPTION_SIGN, replace);
}

bool Sign::get_is_blocking() const
{
  return true;
}

string Sign::get_text_sid() const
{
  return text_sid;
}

bool Sign::serialize(ostream& stream) const
{
  Feature::serialize(stream);
  Serialize::write_string(stream, text_sid);

  return true;
}

bool Sign::deserialize(istream& stream)
{
  Feature::deserialize(stream);
  Serialize::read_string(stream, text_sid);

  return true;
}

ClassIdentifier Sign::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SIGN;
}


#ifdef UNIT_TESTS
#include "unit_tests/Sign_test.cpp"
#endif

