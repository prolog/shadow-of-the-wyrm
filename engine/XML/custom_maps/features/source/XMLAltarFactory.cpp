#include "XMLAltarFactory.hpp"
#include "FeatureGenerator.hpp"

using namespace std;

// Read in the altar details from the XML, creating the altar as a
// FeaturePtr.
FeaturePtr XMLAltarFactory::create(const XMLNode& altar_node) const
{
  string deity_id = XMLUtils::get_child_node_value(altar_node, "DeityID");
  AlignmentRange alignment = static_cast<AlignmentRange>(XMLUtils::get_child_node_int_value(altar_node, "Alignment", ALIGNMENT_RANGE_EVIL));

  FeaturePtr altar = FeatureGenerator::generate_altar(deity_id, alignment);
  return altar;
}

