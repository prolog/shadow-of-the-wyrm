#include "FeatureGenerator.hpp"
#include "XMLPulperReader.hpp"

using namespace std;

FeaturePtr XMLPulperReader::create(const XMLNode& pulper_node) const
{
  FeaturePtr pulper = FeatureGenerator::generate_pulper();

  XMLNode material_node = XMLUtils::get_next_element_by_local_name(pulper_node, "Material");

  if (!material_node.is_null())
  {
    pulper->set_material_type(static_cast<MaterialType>(XMLUtils::get_node_int_value(material_node)));
  }

  return pulper;
}

