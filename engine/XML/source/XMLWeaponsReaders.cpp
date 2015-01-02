#include "XMLWeaponsReaders.hpp"

using namespace std;

// Methods for reading in weapons from the XML configuration.
XMLWeaponsReader::XMLWeaponsReader()
{
}

XMLWeaponsReader::~XMLWeaponsReader()
{
}

void XMLWeaponsReader::parse(WeaponPtr weapon, GenerationValues& gv, const XMLNode& weapon_node)
{
  if (weapon && !weapon_node.is_null())
  {
    XMLWearableReader::parse(weapon, gv, weapon_node);
    
    SkillType trained_skill = static_cast<SkillType>(XMLUtils::get_child_node_int_value(weapon_node, "Skill", static_cast<int>(SkillType::SKILL_MELEE_EXOTIC)));
    weapon->set_trained_skill(trained_skill);
    
    SkillType trained_ranged_skill = static_cast<SkillType>(XMLUtils::get_child_node_int_value(weapon_node, "RangedSkill", static_cast<int>(SkillType::SKILL_RANGED_EXOTIC)));
    weapon->set_trained_ranged_skill(trained_ranged_skill);
    
    bool requires_ranged_weapon = XMLUtils::get_child_node_bool_value(weapon_node, "RequiresRangedWeapon", false);
    weapon->set_requires_ranged_weapon(requires_ranged_weapon);
    
    int difficulty = XMLUtils::get_child_node_int_value(weapon_node, "Difficulty");
    weapon->set_difficulty(difficulty);
    
    int speed = XMLUtils::get_child_node_int_value(weapon_node, "Speed");
    weapon->set_speed(speed);
    
    XMLNode damage_node = XMLUtils::get_next_element_by_local_name(weapon_node, "Damage");
    
    Damage weapon_damage;
    parse_damage(weapon_damage, damage_node);
    weapon->set_damage(weapon_damage);

    XMLNode slays_node = XMLUtils::get_next_element_by_local_name(weapon_node, "Slays");

    if (!slays_node.is_null())
    {
      vector<string> slay_races;
      vector<XMLNode> slay_nodes = XMLUtils::get_elements_by_local_name(slays_node, "Slay");

      for (const XMLNode& slay_node : slay_nodes)
      {
        string slay_race = XMLUtils::get_node_value(slay_node);
        slay_races.push_back(slay_race);
      }

      weapon->set_slays_races(slay_races);
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

void XMLAmmunitionReader::parse(WeaponPtr ammunition, GenerationValues& gv, const XMLNode& missile_node)
{
  if (ammunition && !missile_node.is_null())
  {
    XMLWeaponsReader::parse(ammunition, gv, missile_node);
  }
}

