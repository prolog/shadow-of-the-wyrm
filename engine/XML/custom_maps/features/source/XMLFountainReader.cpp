#include "FeatureGenerator.hpp"
#include "XMLFountainReader.hpp"

using namespace std;

// Read in a FeaturePtr representing a Fountain, given a Fountain XML
// node (see CustomMap.xsd for details)
FeaturePtr XMLFountainReader::create(const XMLNode& fountain_node) const
{
  FeaturePtr fountain = FeatureGenerator::generate_fountain();

  XMLNode material_node = XMLUtils::get_next_element_by_local_name(fountain_node, "Material");
  if (!material_node.is_null())
  {
    fountain->set_material_type(static_cast<MaterialType>(XMLUtils::get_node_int_value(material_node)));
  }

  return fountain;
}

