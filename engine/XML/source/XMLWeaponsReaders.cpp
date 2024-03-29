#include "XMLWeaponsReaders.hpp"
#include "CombatConstants.hpp"

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

    int range = XMLUtils::get_child_node_int_value(weapon_node, "Range", 1);
    weapon->set_range(range);

    int difficulty = XMLUtils::get_child_node_int_value(weapon_node, "Difficulty");
    weapon->set_difficulty(difficulty);
    
    int speed = XMLUtils::get_child_node_int_value(weapon_node, "Speed");
    weapon->set_speed(speed);
    
    XMLNode damage_node = XMLUtils::get_next_element_by_local_name(weapon_node, "Damage");
    
    Damage weapon_damage;
    parse_damage(weapon_damage, damage_node);

    if (weapon->get_artifact())
    {
      int effect_bonus = weapon_damage.get_effect_bonus();
      effect_bonus = std::max<int>(effect_bonus, CombatConstants::MIN_ARTIFACT_EFFECT_BONUS);
     
      weapon_damage.set_effect_bonus(effect_bonus);
    }

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

void XMLAmmunitionReader::parse(WeaponPtr ammunition, GenerationValues& gv, const XMLNode& missile_node)
{
  if (ammunition && !missile_node.is_null())
  {
    XMLWeaponsReader::parse(ammunition, gv, missile_node);
  }
}

