#include "FeatureGenerator.hpp"
#include "XMLPewReader.hpp"

using namespace std;

// Read in a Pew from the given Pew XML node, returning the result as
// a FeaturePtr.
FeaturePtr XMLPewReader::create(const XMLNode& pew_node) const
{
  PewDirection pew_direction = static_cast<PewDirection>(XMLUtils::get_child_node_int_value(pew_node, "Orientation", PEW_DIRECTION_NORTH_SOUTH));
  FeaturePtr pew = FeatureGenerator::generate_pew(pew_direction);
  return pew;
}

