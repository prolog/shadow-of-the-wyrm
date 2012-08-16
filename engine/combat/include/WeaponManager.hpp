#pragma once
#include "AttackTypes.hpp"
#include "Creature.hpp"
#include "Weapon.hpp"

class WeaponManager
{
  public:
    WeaponPtr get_weapon(CreaturePtr creature, const AttackType attack_type);
    SkillType get_skill_type(CreaturePtr creature, const AttackType attack_type);
    WeaponStyle get_style(const AttackType attack_type);
    int get_difficulty(WeaponPtr weapon);
    Damage get_damage(CreaturePtr creature, const AttackType attack_type);
    DamageType get_damage_type(CreaturePtr attacking_creature, const AttackType attack_type);
    SkillType get_appropriate_trained_skill(WeaponPtr weapon, const AttackType attack_type);
    
  protected:
    Damage get_melee_weapon_damage(CreaturePtr creature, const AttackType attack_type);
    Damage get_ranged_weapon_damage(CreaturePtr creature);
};
