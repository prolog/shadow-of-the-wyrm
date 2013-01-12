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
    // else if ...
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