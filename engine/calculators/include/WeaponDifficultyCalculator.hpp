#pragma once
#include "AttackTypes.hpp"
#include "Creature.hpp"
#include "Weapon.hpp"

class WeaponDifficultyCalculator
{
  public:
    int calculate_base_difficulty(CreaturePtr creature, const AttackType attack_type);
    int get_difficulty_for_weapon(WeaponPtr weapon);
    int calculate_total_difficulty_for_display(CreaturePtr creature, const AttackType attack_type);
};
