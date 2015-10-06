#include <boost/algorithm/string/replace.hpp>
#include "FeatureDescriber.hpp"
#include "MaterialTextKeys.hpp"
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
    string desc_feature = StringTable::get(full_desc.first);

    for (const string& replacement_str_sid : replacements)
    {
      boost::replace_first(desc_feature, "%s", StringTable::get(replacement_str_sid));
    }

    ostringstream desc_s;
    string material;
    desc_s << desc_feature << " (" << MaterialTextKeys::get_material(feature->get_material_type()) << ")";
    description = desc_s.str();
  }

  return description;
}
