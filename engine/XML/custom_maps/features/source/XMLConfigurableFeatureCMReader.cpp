#include "FeatureGenerator.hpp"
#include "XMLConfigurableFeatureCMReader.hpp"

using namespace std;

FeaturePtr XMLConfigurableFeatureCMReader::create(const XMLNode& cf_node) const
{
  FeaturePtr cf;

  if (!cf_node.is_null())
  {
    string id = XMLUtils::get_attribute_value(cf_node, "id");
    
    MaterialType material = static_cast<MaterialType>(XMLUtils::get_child_node_int_value(cf_node, "Material", static_cast<int>(MaterialType::MATERIAL_TYPE_WOOD)));
    string symbol_s = XMLUtils::get_child_node_value(cf_node, "Symbol");
    uchar symbol = '?';

    if (!symbol_s.empty())
    {
      symbol = symbol_s.at(0);
    }

    Colour colour = static_cast<Colour>(XMLUtils::get_child_node_int_value(cf_node, "Colour"));
    string desc_sid = XMLUtils::get_child_node_value(cf_node, "DescriptionSID");

    if (!id.empty())
    {
      cf = FeatureGenerator::generate_configurable_feature(id);
    }
  }

  return cf;
}
