#include "XMLConfigurableFeatureReader.hpp"
#include "FeatureGenerator.hpp"

using namespace std;

FeatureMap XMLConfigurableFeatureReader::get_configurable_features(const XMLNode& config_features_node)
{
  FeatureMap fm;

  if (!config_features_node.is_null())
  {
    vector<XMLNode> config_feature_nodes = XMLUtils::get_elements_by_local_name(config_features_node, "Feature");

    for (const XMLNode& cf_node : config_feature_nodes)
    {
      FeaturePtr cf = get_configurable_feature(cf_node);

      if (!cf_node.is_null())
      {
        // ids only exist for basic features, which need some sort of
        // differentiation within the basic feature collection on the
        // Game.
        string id = XMLUtils::get_attribute_value(cf_node, "id");
        fm[id] = cf;
      }
    }
  }

  return fm;
}

FeaturePtr XMLConfigurableFeatureReader::get_configurable_feature(const XMLNode& configurable_feature_node)
{
  FeaturePtr cf;

  if (!configurable_feature_node.is_null())
  {
    MaterialType mt = static_cast<MaterialType>(XMLUtils::get_child_node_int_value(configurable_feature_node, "Material"));

    string symbol_s = XMLUtils::get_child_node_value(configurable_feature_node, "Symbol");
    uchar symbol = '?';

    if (!symbol_s.empty())
    {
      symbol = symbol_s.at(0);
    }

    Colour colour = static_cast<Colour>(XMLUtils::get_child_node_int_value(configurable_feature_node, "Colour"));
    string desc_sid = XMLUtils::get_child_node_value(configurable_feature_node, "DescriptionSID");
    
    cf = FeatureGenerator::generate_configurable_feature(mt, symbol, colour, desc_sid);
  }

  return cf;
}
