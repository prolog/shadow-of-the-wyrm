#include "FeatureGenerator.hpp"
#include "XMLTanneryReader.hpp"

using namespace std;

FeaturePtr XMLTanneryReader::create(const XMLNode& tannery_node) const
{
  FeaturePtr tannery = FeatureGenerator::generate_tannery();

  XMLNode material_node = XMLUtils::get_next_element_by_local_name(tannery_node, "Material");

  if (!material_node.is_null())
  {
    tannery->set_material_type(static_cast<MaterialType>(XMLUtils::get_node_int_value(material_node)));
  }

  return tannery;
}

