#pragma once
#include "AttackTypes.hpp"
#include "Creature.hpp"
#include "Weapon.hpp"

class WeaponManager
{
  public:
    bool is_using_weapon(CreaturePtr creature, const AttackType attack_type);
    WeaponPtr get_weapon(CreaturePtr creature, const AttackType attack_type);
    ItemPtr get_item(CreaturePtr creature, const AttackType attack_type);
    std::vector<std::string> get_slays_races(CreaturePtr creature, const AttackType attack_type);
    SkillType get_skill_type(CreaturePtr creature, const AttackType attack_type);
    WeaponStyle get_style(const AttackType attack_type);
    int get_difficulty(WeaponPtr weapon);
    Damage get_damage(CreaturePtr creature, const AttackType attack_type);
    DamageType get_damage_type(CreaturePtr attacking_creature, const AttackType attack_type);
    SkillType get_appropriate_trained_skill(WeaponPtr weapon, const AttackType attack_type);
    bool is_ranged_weapon_skill_type_compatible_with_ammunition(WeaponPtr ranged_weapon, WeaponPtr ammunition);
    bool do_trained_ranged_skills_match(WeaponPtr ranged_weapon, WeaponPtr ammunition);
    
  protected:
    Damage get_melee_weapon_damage(CreaturePtr creature, const AttackType attack_type);
    Damage get_ranged_weapon_damage(CreaturePtr creature);
    
};
