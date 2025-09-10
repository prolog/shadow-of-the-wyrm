#include "FeatureGenerator.hpp"
#include "XMLCauldronReader.hpp"

using namespace std;

FeaturePtr XMLCauldronReader::create(const XMLNode& cauldron_node) const
{
  FeaturePtr cauldron = FeatureGenerator::generate_cauldron();

  if (!cauldron_node.is_null())
  {
    MaterialType material = static_cast<MaterialType>(XMLUtils::get_child_node_int_value(cauldron_node, "Material", static_cast<int>(MaterialType::MATERIAL_TYPE_WOOD)));
    cauldron->set_material_type(material);
  }

  return cauldron;
}

