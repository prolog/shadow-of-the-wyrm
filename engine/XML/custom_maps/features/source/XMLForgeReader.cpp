#include "FeatureGenerator.hpp"
#include "XMLForgeReader.hpp"

using namespace std;

FeaturePtr XMLForgeReader::create(const XMLNode& forge_node) const
{
  FeaturePtr forge = FeatureGenerator::generate_forge();

  XMLNode material_node = XMLUtils::get_next_element_by_local_name(forge_node, "Material");

  if (!material_node.is_null())
  {
    forge->set_material_type(static_cast<MaterialType>(XMLUtils::get_node_int_value(material_node)));
  }

  return forge;
}

