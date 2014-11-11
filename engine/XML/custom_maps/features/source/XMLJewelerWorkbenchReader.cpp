#include "FeatureGenerator.hpp"
#include "XMLJewelerWorkbenchReader.hpp"

using namespace std;

FeaturePtr XMLJewelerWorkbenchReader::create(const XMLNode& workbench_node) const
{
  FeaturePtr workbench = FeatureGenerator::generate_jeweler_workbench();

  XMLNode material_node = XMLUtils::get_next_element_by_local_name(workbench_node, "Material");

  if (!material_node.is_null())
  {
    workbench->set_material_type(static_cast<MaterialType>(XMLUtils::get_node_int_value(material_node)));
  }

  return workbench;
}

