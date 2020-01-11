#include "XMLBarrelReader.hpp"
#include "FeatureGenerator.hpp"

using namespace std;

// Read in the details of a barrel from the XML, returning a FeaturePtr.
FeaturePtr XMLBarrelReader::create(const XMLNode& barrel_node) const
{
  FeaturePtr fbarrel = FeatureGenerator::generate_barrel();
  std::shared_ptr<Barrel> barrel = dynamic_pointer_cast<Barrel>(fbarrel);

  if (barrel != nullptr)
  {
    bool tap = XMLUtils::get_child_node_bool_value(barrel_node, "Tap", barrel->get_tap());
    barrel->set_tap(tap);

    string pour_item_id = XMLUtils::get_child_node_value(barrel_node, "Pour");
    barrel->set_pour_item_id(pour_item_id);
  }

  return barrel;
}

