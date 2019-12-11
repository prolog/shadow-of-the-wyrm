#include "FeatureDescriptionTextKeys.hpp"
#include "MaterialFactory.hpp"
#include "Serialize.hpp"
#include "Sign.hpp"

using namespace std;

Sign::Sign(const Symbol& new_symbol, const string& new_text_sid)
: Feature(new_text_sid, MaterialType::MATERIAL_TYPE_WOOD, AlignmentRange::ALIGNMENT_RANGE_NEUTRAL, new_symbol)
{
}

Feature* Sign::clone()
{
  return new Sign(*this);
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

ClassIdentifier Sign::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SIGN;
}

#ifdef UNIT_TESTS
#include "unit_tests/Sign_test.cpp"
#endif

