#include "XMLBarrelReader.hpp"
#include "Barrel.hpp"

using namespace std;

// Read in the details of a barrel from the XML, returning a FeaturePtr.
FeaturePtr XMLBarrelReader::create(const XMLNode& barrel_node) const
{
  std::shared_ptr<Barrel> barrel = std::make_shared<Barrel>();

  bool tap = XMLUtils::get_child_node_bool_value(barrel_node, "Tap", barrel->get_tap());
  barrel->set_tap(tap);

  string pour_item_id = XMLUtils::get_child_node_value(barrel_node, "Pour");
  barrel->set_pour_item_id(pour_item_id);

  return barrel;
}

