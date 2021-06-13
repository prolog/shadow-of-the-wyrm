#include "FeatureGenerator.hpp"
#include "XMLKilnReader.hpp"

using namespace std;

FeaturePtr XMLKilnReader::create(const XMLNode& forge_node) const
{
  FeaturePtr kiln = FeatureGenerator::generate_kiln();

  XMLNode material_node = XMLUtils::get_next_element_by_local_name(forge_node, "Material");

  if (!material_node.is_null())
  {
    kiln->set_material_type(static_cast<MaterialType>(XMLUtils::get_node_int_value(material_node)));
  }

  return kiln;
}

