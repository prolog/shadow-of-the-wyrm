#include <string>
#include "AlignmentEnums.hpp"
#include "FeatureGenerator.hpp"
#include "XMLMapFeatureFactory.hpp"

using namespace std;

XMLMapFeatureFactory::XMLMapFeatureFactory()
{
}

XMLMapFeatureFactory::~XMLMapFeatureFactory()
{
}

FeaturePtr XMLMapFeatureFactory::create_feature(const XMLNode& feature_placement_node)
{
  FeaturePtr feature;

  if (!feature_placement_node.is_null())
  {
    XMLNode feature_node;

    if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Altar")).is_null())
    {
      feature = create_altar(feature_node);
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Door")).is_null())
    {
      feature = create_door(feature_node);
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Pew")).is_null())
    {
      feature = create_pew(feature_node);
    }
  }

  return feature;
}

// Create an altar, reading in the alignment and the deity ID.
FeaturePtr XMLMapFeatureFactory::create_altar(const XMLNode& altar_node)
{
  string deity_id = XMLUtils::get_child_node_value(altar_node, "DeityID");
  AlignmentRange alignment = static_cast<AlignmentRange>(XMLUtils::get_child_node_int_value(altar_node, "Alignment", ALIGNMENT_RANGE_EVIL));

  FeaturePtr altar = FeatureGenerator::generate_altar(deity_id, alignment);
  return altar;
}

// Create a door, reading in its material, entrance state, key info, etc., from the XML.
FeaturePtr XMLMapFeatureFactory::create_door(const XMLNode& door_node)
{
  FeaturePtr door = FeatureGenerator::generate_door();

  MaterialType material = static_cast<MaterialType>(XMLUtils::get_child_node_int_value(door_node, "Material", MATERIAL_TYPE_WOOD));
  door->set_material_type(material);

  return door;
}

// Create a pew, reading its orientation (n/s, e/w) from the XML.
FeaturePtr XMLMapFeatureFactory::create_pew(const XMLNode& pew_node)
{
  PewDirection pew_direction = static_cast<PewDirection>(XMLUtils::get_child_node_int_value(pew_node, "Orientation", PEW_DIRECTION_NORTH_SOUTH));
  FeaturePtr pew = FeatureGenerator::generate_pew(pew_direction);
  return pew;
}