#include "FeatureGenerator.hpp"
#include "XMLHiveReader.hpp"

using namespace std;

FeaturePtr XMLHiveReader::create(const XMLNode& hive_node) const
{
  FeaturePtr hive = FeatureGenerator::generate_hive();

  if (!hive_node.is_null())
  {
    MaterialType material = static_cast<MaterialType>(XMLUtils::get_child_node_int_value(hive_node, "Material", static_cast<int>(MaterialType::MATERIAL_TYPE_WOOD)));
    hive->set_material_type(material);
  }

  return hive;
}

