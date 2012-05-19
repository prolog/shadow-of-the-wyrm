#include "XMLWeaponsReaders.hpp"

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
    
    int difficulty = XMLUtils::get_child_node_int_value(weapon_node, "Difficulty");
    weapon->set_difficulty(difficulty);
    
    XMLNode damage_node = XMLUtils::get_next_element_by_local_name(weapon_node, "Damage");
    
    Damage weapon_damage;
    parse_damage(weapon_damage, damage_node);
    weapon->set_damage(weapon_damage);
  }
}


// Methods for reading in Ammunition
XMLAmmunitionReader::XMLAmmunitionReader()
{
}

XMLAmmunitionReader::~XMLAmmunitionReader()
{
}

void XMLAmmunitionReader::parse(AmmunitionPtr ammunition, const XMLNode& missile_node)
{
  if (ammunition && !missile_node.is_null())
  {
    XMLWearableReader::parse(ammunition, missile_node);
  }
}

