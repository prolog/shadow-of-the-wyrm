#include "FeatureGenerator.hpp"
#include "XMLBasicFeatureCMReader.hpp"

using namespace std;

FeaturePtr XMLBasicFeatureCMReader::create(const XMLNode& bf_node) const
{
  FeaturePtr bf;

  if (!bf_node.is_null())
  {
    string id = XMLUtils::get_attribute_value(bf_node, "id");
    
    MaterialType material = static_cast<MaterialType>(XMLUtils::get_child_node_int_value(bf_node, "Material", static_cast<int>(MaterialType::MATERIAL_TYPE_WOOD)));
    string symbol_s = XMLUtils::get_child_node_value(bf_node, "Symbol");
    uchar symbol = '?';

    if (!symbol_s.empty())
    {
      symbol = symbol_s.at(0);
    }

    Colour colour = static_cast<Colour>(XMLUtils::get_child_node_int_value(bf_node, "Colour"));
    string desc_sid = XMLUtils::get_child_node_value(bf_node, "DescriptionSID");

    if (!id.empty())
    {
      bf = FeatureGenerator::generate_basic_feature(id);
    }
    else
    {
      bf = FeatureGenerator::generate_basic_feature(material, symbol, colour, desc_sid);
    }
  }

  return bf;
}

