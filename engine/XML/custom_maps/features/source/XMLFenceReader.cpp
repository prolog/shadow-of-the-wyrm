#include "FeatureGenerator.hpp"
#include "XMLFenceReader.hpp"

using namespace std;

FeaturePtr XMLFenceReader::create(const XMLNode& fence_node) const
{
  FeaturePtr fence = FeatureGenerator::generate_fence();

  XMLNode material_node = XMLUtils::get_next_element_by_local_name(fence_node, "Material");

  if (!material_node.is_null())
  {
    fence->set_material_type(static_cast<MaterialType>(XMLUtils::get_node_int_value(material_node)));
  }

  return fence;
}

