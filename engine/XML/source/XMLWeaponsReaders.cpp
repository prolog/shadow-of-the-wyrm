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

