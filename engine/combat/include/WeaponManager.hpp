#pragma once
#include "AttackTypes.hpp"
#include "Creature.hpp"
#include "Weapon.hpp"

class WeaponManager
{
  public:
    WeaponPtr get_weapon(CreaturePtr creature, const AttackType attack_type);
    Damage get_damage(CreaturePtr creature, AttackType attack_type);
    DamageType get_damage_type(CreaturePtr attacking_creature, const AttackType attack_type);
};
