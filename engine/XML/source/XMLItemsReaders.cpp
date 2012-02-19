#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include "MaterialFactory.hpp"
#include "XMLItemsReaders.hpp"
#include "MiscItem.hpp"

using namespace std;
using boost::make_shared;

XMLItemsReader::XMLItemsReader()
{
}

XMLItemsReader::~XMLItemsReader()
{
}

// Gets all the items of the various types and returns them in a map,
// keyed by their ID (specified in the XML).
ItemMap XMLItemsReader::get_items(const XMLNode& items_node)
{
  ItemMap items;
  
  if (!items_node.is_null())
  {
    XMLNode armours_node = XMLUtils::get_next_element_by_local_name(items_node, "Armours");
    
    if (!armours_node.is_null())
    {
      ItemMap armours_map = get_armour(armours_node);
      items.insert(armours_map.begin(), armours_map.end());
    }
    
    XMLNode weapons_node = XMLUtils::get_next_element_by_local_name(items_node, "Weapons");
    
    if (!weapons_node.is_null())
    {
      ItemMap weapons_map = get_weapons(weapons_node);
      items.insert(weapons_map.begin(), weapons_map.end());
    }
    
    XMLNode ranged_weapons_node = XMLUtils::get_next_element_by_local_name(items_node, "RangedWeapons");
    
    if (!ranged_weapons_node.is_null())
    {
      ItemMap ranged_weapons_map = get_ranged_weapons(ranged_weapons_node);
      items.insert(ranged_weapons_map.begin(), ranged_weapons_map.end());
    }
    
    XMLNode misc_items_node = XMLUtils::get_next_element_by_local_name(items_node, "MiscItems");
    
    if (!misc_items_node.is_null())
    {
      ItemMap misc_items_map = get_misc_items(misc_items_node);
      items.insert(misc_items_map.begin(), misc_items_map.end());
    }    
  }
  
  return items;
}

ItemMap XMLItemsReader::get_misc_items(const XMLNode& misc_items_node)
{
  ItemMap misc_items;
  
  if (!misc_items_node.is_null())
  {
    vector<XMLNode> misc_items_nodes = XMLUtils::get_elements_by_local_name(misc_items_node, "Item");
    
    BOOST_FOREACH(XMLNode node, misc_items_nodes)
    {
      if (!node.is_null())
      {
        ItemPtr item = make_shared<MiscItem>();
        item_reader.parse(item, node);
        misc_items.insert(make_pair(item->get_id(), item));  
      }
    }
  }
  
  return misc_items;
}

ItemMap XMLItemsReader::get_armour(const XMLNode& armours_node)
{
  ItemMap armour_map;
  
  if (!armours_node.is_null())
  {
    vector<XMLNode> armour_nodes = XMLUtils::get_elements_by_local_name(armours_node, "Armour");
    
    BOOST_FOREACH(XMLNode node, armour_nodes)
    {
      if (!node.is_null())
      {
        ArmourPtr armour = make_shared<Armour>();
        armour_reader.parse(armour, node);
        armour_map.insert(make_pair(armour->get_id(), armour));
      }
    }
  }
  
  return armour_map;
}

ItemMap XMLItemsReader::get_weapons(const XMLNode& weapons_node)
{
  ItemMap weapons_map;
  
  if (!weapons_node.is_null())
  {
    vector<XMLNode> weapons_nodes = XMLUtils::get_elements_by_local_name(weapons_node, "Weapon");
    
    BOOST_FOREACH(XMLNode node, weapons_nodes)
    {
      MeleeWeaponPtr weapon = make_shared<MeleeWeapon>();
      weapons_reader.parse(weapon, node);
      weapons_map.insert(make_pair(weapon->get_id(), weapon));
    }
  }

  return weapons_map;
}

ItemMap XMLItemsReader::get_ranged_weapons(const XMLNode& ranged_weapons_node)
{
  ItemMap weapons_map;
  
  if (!ranged_weapons_node.is_null())
  {
    vector<XMLNode> ranged_weapons_nodes = XMLUtils::get_elements_by_local_name(ranged_weapons_node, "Weapon");
    
    BOOST_FOREACH(XMLNode node, ranged_weapons_nodes)
    {
      RangedWeaponPtr ranged_weapon = make_shared<RangedWeapon>();
      weapons_reader.parse(ranged_weapon, node);
      weapons_map.insert(make_pair(ranged_weapon->get_id(), ranged_weapon));
    }
  }
  
  return weapons_map;
}

// Methods for reading in the base item details
XMLItemReader::XMLItemReader()
{
}

XMLItemReader::~XMLItemReader()
{
}

void XMLItemReader::parse(ItemPtr item, const XMLNode& item_node)
{
  if (item && !item_node.is_null())
  {    
    string id = XMLUtils::get_attribute_value(item_node, "id");
    item->set_id(id);

    string description_sid = XMLUtils::get_child_node_value(item_node, "DescriptionSID");
    item->set_description_sid(description_sid);

    XMLNode weight_node = XMLUtils::get_next_element_by_local_name(item_node, "Weight");
    
    if (!weight_node.is_null())
    {
      Weight weight;
      
      uint pounds = static_cast<uint>(XMLUtils::get_child_node_int_value(weight_node, "Pounds"));
      uint ounces = static_cast<uint>(XMLUtils::get_child_node_int_value(weight_node, "Ounces"));
      
      weight.set_weight(pounds, ounces);
            
      item->set_weight(weight);
    }

    EquipmentWornLocation location = static_cast<EquipmentWornLocation>(XMLUtils::get_child_node_int_value(item_node, "WornLocation", EQUIPMENT_WORN_NONE));
    item->set_worn_location(location);

    ItemStatus status = static_cast<ItemStatus>(XMLUtils::get_child_node_int_value(item_node, "ItemStatus"));
    item->set_status(status);
    
    bool is_artifact = XMLUtils::get_child_node_bool_value(item_node, "Artifact");
    item->set_artifact(is_artifact);
    
    MaterialType material_type = static_cast<MaterialType>(XMLUtils::get_child_node_int_value(item_node, "Material", MATERIAL_TYPE_WOOD));
    MaterialPtr material = MaterialFactory::create_material(material_type);
    item->set_material(material);
  }
}

// Methods for reading in armour from the XML configuration.
XMLArmourReader::XMLArmourReader()
{
}

XMLArmourReader::~XMLArmourReader()
{
}

void XMLArmourReader::parse(ArmourPtr armour, const XMLNode& armour_node)
{
  if (armour && !armour_node.is_null())
  {
    XMLWearableReader::parse(armour, armour_node);
  }
}

// Methods for reading in weapons from the XML configuration.
XMLWeaponsReader::XMLWeaponsReader()
{
}

XMLWeaponsReader::~XMLWeaponsReader()
{
}

void XMLWeaponsReader::parse(WeaponPtr weapon, const XMLNode& weapon_node)
{
  if (weapon && !weapon_node.is_null())
  {
    XMLWearableReader::parse(weapon, weapon_node);
    
    SkillType trained_skill = static_cast<SkillType>(XMLUtils::get_child_node_int_value(weapon_node, "Skill"));
    weapon->set_trained_skill(trained_skill);
    
    XMLNode damage_node = XMLUtils::get_next_element_by_local_name(weapon_node, "Damage");
    
    if (!damage_node.is_null())
    {
      Damage weapon_damage;
      
      uint num_sides = static_cast<uint>(XMLUtils::get_child_node_int_value(damage_node, "NumSides"));
      weapon_damage.set_dice_sides(num_sides);

      uint num_dice = static_cast<uint>(XMLUtils::get_child_node_int_value(damage_node, "NumDice"));
      weapon_damage.set_num_dice(num_dice);
      
      int modifier = XMLUtils::get_child_node_int_value(damage_node, "Modifier");
      weapon_damage.set_modifier(modifier);
      
      DamageType damage_type = static_cast<DamageType>(XMLUtils::get_child_node_int_value(damage_node, "Type"));
      weapon_damage.set_damage_type(damage_type);
      
      weapon->set_damage(weapon_damage);
    }
  }
}

// Methods for reading in the common elements of all Wearable items.
XMLWearableReader::XMLWearableReader()
{
}

XMLWearableReader::~XMLWearableReader()
{
}

void XMLWearableReader::parse(WearablePtr wearable, const XMLNode& wearable_node)
{
  if (wearable && !wearable_node.is_null())
  {
    XMLItemReader::parse(wearable, wearable_node);
    
    int evade = XMLUtils::get_child_node_int_value(wearable_node, "Evade");
    wearable->set_evade(evade);
    
    int soak = XMLUtils::get_child_node_int_value(wearable_node, "Soak");
    wearable->set_soak(soak);
  }
}
