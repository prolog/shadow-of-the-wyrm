#include <boost/algorithm/string/replace.hpp>
#include "FeatureDescriber.hpp"
#include "StringTable.hpp"

using namespace std;

FeatureDescriber::FeatureDescriber(FeaturePtr feat)
: feature(feat)
{
}

string FeatureDescriber::describe() const
{
  string description;

  if (feature)
  {
    pair<string, vector<string>> full_desc = feature->get_description_and_replacement_sids();
    vector<string> replacements = full_desc.second;
    description = StringTable::get(full_desc.first);

    for (const string& replacement_str_sid : replacements)
    {
      boost::replace_first(description, "%s", StringTable::get(replacement_str_sid));
    }
  }

  return description;
}
