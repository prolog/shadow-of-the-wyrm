#include "FeatureGenerator.hpp"
#include "XMLStoneMarkerReader.hpp"

using namespace std;

FeaturePtr XMLStoneMarkerReader::create(const XMLNode& sm_node) const
{
  FeaturePtr sm = FeatureGenerator::generate_stone_marker();

  if (!sm_node.is_null())
  {
    MaterialType material = static_cast<MaterialType>(XMLUtils::get_child_node_int_value(sm_node, "Material", static_cast<int>(MaterialType::MATERIAL_TYPE_STONE)));
    sm->set_material_type(material);
  }

  return sm;
}

