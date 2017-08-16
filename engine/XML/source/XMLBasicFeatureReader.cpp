#include "XMLBasicFeatureReader.hpp"
#include "FeatureGenerator.hpp"

using namespace std;

FeatureMap XMLBasicFeatureReader::get_basic_features(const XMLNode& basic_features_node)
{
  FeatureMap fm;

  if (!basic_features_node.is_null())
  {
    vector<XMLNode> basic_feature_nodes = XMLUtils::get_elements_by_local_name(basic_features_node, "Feature");

    for (const XMLNode& bf_node : basic_feature_nodes)
    {
      FeaturePtr bf = get_basic_feature(bf_node);

      if (!bf_node.is_null())
      {
        // ids only exist for basic features, which need some sort of
        // differentiation within the basic feature collection on the
        // Game.
        string id = XMLUtils::get_attribute_value(bf_node, "id");
        fm[id] = bf;
      }
    }
  }

  return fm;
}

FeaturePtr XMLBasicFeatureReader::get_basic_feature(const XMLNode& basic_feature_node)
{
  FeaturePtr bf;

  if (!basic_feature_node.is_null())
  {
    MaterialType mt = static_cast<MaterialType>(XMLUtils::get_child_node_int_value(basic_feature_node, "Material"));

    string symbol_s = XMLUtils::get_child_node_value(basic_feature_node, "Symbol");
    uchar symbol = '?';

    if (!symbol_s.empty())
    {
      symbol = symbol_s.at(0);
    }

    Colour colour = static_cast<Colour>(XMLUtils::get_child_node_int_value(basic_feature_node, "Colour"));
    string desc_sid = XMLUtils::get_child_node_value(basic_feature_node, "DescriptionSID");
    
    bf = FeatureGenerator::generate_basic_feature(mt, symbol, colour, desc_sid);
  }

  return bf;
}
