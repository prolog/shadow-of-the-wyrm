#include "FeatureGenerator.hpp"
#include "XMLDoorReader.hpp"

using namespace std;

// Read in a Door (as a FeaturePtr) based on the given Door xml node.
FeaturePtr XMLDoorReader::create(const XMLNode& door_node) const
{
  DoorPtr door = FeatureGenerator::generate_door();

  string lock_id = XMLUtils::get_child_node_value(door_node, "LockID");
  if (!lock_id.empty())
  {
    LockPtr lock = std::make_shared<Lock>(lock_id, true);
    door->set_lock(lock);
  }

  MaterialType material = static_cast<MaterialType>(XMLUtils::get_child_node_int_value(door_node, "Material", static_cast<int>(MaterialType::MATERIAL_TYPE_WOOD)));
  door->set_material_type(material);

  XMLNode entrance_node = XMLUtils::get_next_element_by_local_name(door_node, "Entrance");

  if (!entrance_node.is_null())
  {
    EntranceStateType entrance_state = static_cast<EntranceStateType>(XMLUtils::get_child_node_int_value(entrance_node, "EntranceState", static_cast<int>(EntranceStateType::ENTRANCE_TYPE_OPEN)));
    door->get_state_ref().set_state(entrance_state);
  }

  return door;
}

