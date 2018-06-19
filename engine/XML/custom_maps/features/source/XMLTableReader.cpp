#include "FeatureGenerator.hpp"
#include "XMLTableReader.hpp"

using namespace std;

FeaturePtr XMLTableReader::create(const XMLNode& table_node) const
{
  FeaturePtr table = FeatureGenerator::generate_table();

  if (!table_node.is_null())
  {
    MaterialType material = static_cast<MaterialType>(XMLUtils::get_child_node_int_value(table_node, "Material", static_cast<int>(MaterialType::MATERIAL_TYPE_STONE)));
    table->set_material_type(material);
  }

  return table;
}

