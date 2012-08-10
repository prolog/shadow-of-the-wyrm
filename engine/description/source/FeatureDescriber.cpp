#include "FeatureDescriber.hpp"
#include "StringTable.hpp"

using std::string;

FeatureDescriber::FeatureDescriber(FeaturePtr feat)
: feature(feat)
{
}

string FeatureDescriber::describe() const
{
  string description;

  if (feature)
  {
    description = StringTable::get(feature->get_description_sid());
  }

  return description;
}
