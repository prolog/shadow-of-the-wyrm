#include <string>
#include "AlignmentEnums.hpp"
#include "Barrel.hpp"
#include "EntranceTypes.hpp"
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
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Barrel")).is_null())
    {
      feature = create_barrel(feature_node);
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Door")).is_null())
    {
      feature = create_door(feature_node);
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Pew")).is_null())
    {
      feature = create_pew(feature_node);
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Sarcophagus")).is_null())
    {
      feature = create_sarcophagus(feature_node);
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

// Create a barrel, reading in the information about the liquid stored within,
// if applicable.
FeaturePtr XMLMapFeatureFactory::create_barrel(const XMLNode& barrel_node)
{
  std::shared_ptr<Barrel> barrel = std::make_shared<Barrel>();

  bool tap = XMLUtils::get_child_node_bool_value(barrel_node, "Tap", barrel->get_tap());
  barrel->set_tap(tap);

  string pour_item_id = XMLUtils::get_child_node_value(barrel_node, "Pour");
  barrel->set_pour_item_id(pour_item_id);

  return barrel;
}

// Create a door, reading in its material, entrance state, key info, etc., from the XML.
FeaturePtr XMLMapFeatureFactory::create_door(const XMLNode& door_node)
{
  DoorPtr door = FeatureGenerator::generate_door();

  string lock_id = XMLUtils::get_child_node_value(door_node, "LockID");
  if (!lock_id.empty())
  {
    LockPtr lock = std::make_shared<Lock>(lock_id, true);
    door->set_lock(lock);
  }

  MaterialType material = static_cast<MaterialType>(XMLUtils::get_child_node_int_value(door_node, "Material", MATERIAL_TYPE_WOOD));
  door->set_material_type(material);

  // JCD FIXME: Refactor this (plus invididual features) into appropriate new files).
  XMLNode entrance_node = XMLUtils::get_next_element_by_local_name(door_node, "Entrance");

  if (!entrance_node.is_null())
  {
    EntranceStateType entrance_state = static_cast<EntranceStateType>(XMLUtils::get_child_node_int_value(entrance_node, "EntranceState", ENTRANCE_TYPE_OPEN));
    door->get_state_ref().set_state(entrance_state);
  }

  return door;
}

// Create a pew, reading its orientation (n/s, e/w) from the XML.
FeaturePtr XMLMapFeatureFactory::create_pew(const XMLNode& pew_node)
{
  PewDirection pew_direction = static_cast<PewDirection>(XMLUtils::get_child_node_int_value(pew_node, "Orientation", PEW_DIRECTION_NORTH_SOUTH));
  FeaturePtr pew = FeatureGenerator::generate_pew(pew_direction);
  return pew;
}

// Create a sarcophagus, reading its material, inscription, any items stored
// within, etc.
FeaturePtr XMLMapFeatureFactory::create_sarcophagus(const XMLNode& sarcophagus_node)
{
  MaterialType material_type = MATERIAL_TYPE_STONE;
  XMLNode material_node = XMLUtils::get_next_element_by_local_name(sarcophagus_node, "Material");
  if (!material_node.is_null())
  {
    material_type = static_cast<MaterialType>(XMLUtils::get_node_int_value(sarcophagus_node));
  }

  SarcophagusPtr sarcophagus = FeatureGenerator::generate_sarcophagus(material_type);

  string inscription_sid = XMLUtils::get_child_node_value(sarcophagus_node, "Inscription");
  sarcophagus->set_inscription_sid(inscription_sid);

  return sarcophagus;
}