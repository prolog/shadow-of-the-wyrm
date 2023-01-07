#include "FeatureGenerator.hpp"
#include "XMLBenchReader.hpp"

using namespace std;

FeaturePtr XMLBenchReader::create(const XMLNode& workbench_node) const
{
  FeaturePtr bench = FeatureGenerator::generate_bench();

  XMLNode material_node = XMLUtils::get_next_element_by_local_name(workbench_node, "Material");

  if (!material_node.is_null())
  {
    bench->set_material_type(static_cast<MaterialType>(XMLUtils::get_node_int_value(material_node)));
  }

  return bench;
}

