#include "XMLConfigurableFeatureReader.hpp"
#include "FeatureGenerator.hpp"

using namespace std;

FeatureMap XMLConfigurableFeatureReader::get_configurable_features(const XMLNode& config_features_node, const bool force_ascii)
{
  FeatureMap fm;

  if (!config_features_node.is_null())
  {
    vector<XMLNode> config_feature_nodes = XMLUtils::get_elements_by_local_name(config_features_node, "ConfigurableFeature");

    for (const XMLNode& cf_node : config_feature_nodes)
    {
      FeaturePtr cf = get_configurable_feature(cf_node, force_ascii);

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

FeaturePtr XMLConfigurableFeatureReader::get_configurable_feature(const XMLNode& configurable_feature_node, const bool force_ascii)
{
  FeaturePtr cf;

  if (!configurable_feature_node.is_null())
  {
    MaterialType mt = static_cast<MaterialType>(XMLUtils::get_child_node_int_value(configurable_feature_node, "Material"));
    Symbol s('?', Colour::COLOUR_WHITE);
    XMLNode symbol_node = XMLUtils::get_next_element_by_local_name(configurable_feature_node, "Symbol");
    parse_symbol(s, symbol_node, force_ascii);
    string desc_sid = XMLUtils::get_child_node_value(configurable_feature_node, "DescriptionSID");
    
    cf = FeatureGenerator::generate_configurable_feature(mt, s, desc_sid);
  }

  return cf;
}
