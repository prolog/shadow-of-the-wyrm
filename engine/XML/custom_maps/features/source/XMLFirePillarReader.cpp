#include "FeatureGenerator.hpp"
#include "XMLFirePillarReader.hpp"

// Read in a FirePillar from the XML.
FeaturePtr XMLFirePillarReader::create(const XMLNode& fire_pillar_node) const
{
  FeaturePtr fire_pillar = FeatureGenerator::generate_fire_pillar();

  MaterialType material = static_cast<MaterialType>(XMLUtils::get_child_node_int_value(fire_pillar_node, "Material", MATERIAL_TYPE_STONE));
  fire_pillar->set_material_type(material);

  return fire_pillar;
}

