#include "FeatureGenerator.hpp"
#include "XMLBedReader.hpp"

using namespace std;

FeaturePtr XMLBedReader::create(const XMLNode& bed_node) const
{
  FeaturePtr bed = FeatureGenerator::generate_bed();

  if (!bed_node.is_null())
  {
    MaterialType material = static_cast<MaterialType>(XMLUtils::get_child_node_int_value(bed_node, "Material", static_cast<int>(MaterialType::MATERIAL_TYPE_WOOD)));
    bed->set_material_type(material);
  }

  return bed;
}

