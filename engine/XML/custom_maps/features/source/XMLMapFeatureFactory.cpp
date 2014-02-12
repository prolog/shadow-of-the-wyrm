#include <string>
#include "AlignmentEnums.hpp"
#include "Barrel.hpp"
#include "EntranceTypes.hpp"
#include "FeatureGenerator.hpp"
#include "IXMLFeatureReader.hpp"
#include "XMLAltarReader.hpp"
#include "XMLBarrelReader.hpp"
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
    IXMLFeatureReaderPtr feature_creator;

    XMLNode feature_node;

    if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Altar")).is_null())
    {
      feature_creator = std::make_shared<XMLAltarReader>();
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Barrel")).is_null())
    {
      feature_creator = std::make_shared<XMLBarrelReader>();
    }
    // TODO: Fix these.
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Door")).is_null())
    {
      feature = create_door(feature_node);
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Fountain")).is_null())
    {
      feature = create_fountain(feature_node);
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Pew")).is_null())
    {
      feature = create_pew(feature_node);
    }
    else if (!(feature_node = XMLUtils::get_next_element_by_local_name(feature_placement_node, "Sarcophagus")).is_null())
    {
      feature = create_sarcophagus(feature_node);
    }

    // TODO: Once these are converted, remove the guard
    if (feature_creator != nullptr)
    {
      feature = feature_creator->create(feature_node);
    }
  }

  return feature;
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

FeaturePtr XMLMapFeatureFactory::create_fountain(const XMLNode& fountain_node)
{
  FeaturePtr fountain = FeatureGenerator::generate_fountain();

  XMLNode material_node = XMLUtils::get_next_element_by_local_name(fountain_node, "Material");
  if (!material_node.is_null())
  {
    fountain->set_material_type(static_cast<MaterialType>(XMLUtils::get_node_int_value(material_node)));
  }

  return fountain;
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
    material_type = static_cast<MaterialType>(XMLUtils::get_node_int_value(material_node));
  }

  SarcophagusPtr sarcophagus = FeatureGenerator::generate_sarcophagus(material_type);

  string inscription_sid = XMLUtils::get_child_node_value(sarcophagus_node, "Inscription");
  sarcophagus->set_inscription_sid(inscription_sid);

  return sarcophagus;
}