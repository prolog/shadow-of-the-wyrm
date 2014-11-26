#include "FeatureGenerator.hpp"
#include "XMLWheelAndLoomReader.hpp"

using namespace std;

FeaturePtr XMLWheelAndLoomReader::create(const XMLNode& wheel_and_loom_node) const
{
  FeaturePtr wheel_and_loom = FeatureGenerator::generate_wheel_and_loom();

  XMLNode material_node = XMLUtils::get_next_element_by_local_name(wheel_and_loom_node, "Material");

  if (!material_node.is_null())
  {
    wheel_and_loom->set_material_type(static_cast<MaterialType>(XMLUtils::get_node_int_value(material_node)));
  }

  return wheel_and_loom;
}

