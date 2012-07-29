#pragma once
#include "AttackTypes.hpp"
#include "Creature.hpp"
#include "Weapon.hpp"

class WeaponDifficultyCalculator
{
  public:
    int calculate(CreaturePtr creature, AttackType attack_type);
    int get_difficulty_for_weapon(WeaponPtr weapon);
};
