#include "BlindFeatureDescriber.hpp"
#include "TextKeys.hpp"
#include "StringTable.hpp"

using std::string;

BlindFeatureDescriber::BlindFeatureDescriber()
: FeatureDescriber(FeaturePtr())
{
}

string BlindFeatureDescriber::describe() const
{
  string feature_description = StringTable::get(TextKeys::SOMETHING);
  return feature_description;
}

