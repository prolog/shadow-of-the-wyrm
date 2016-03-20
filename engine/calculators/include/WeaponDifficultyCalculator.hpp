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

  protected:
    int get_difficulty_penalty_for_dual_wield(CreaturePtr creature, WeaponPtr primary_weapon, WeaponPtr secondary_weapon);
    Weight get_max_unpenalized_weapon_weight(CreaturePtr creature);

    static const int BASE_DUAL_DIFFICULTY;
    static const int SKILLED_BASE_DUAL_DIFFICULTY;
    static const int MINIMUM_DUAL_DIFFICULTY;
    static const int HEAVY_WEAPON_PENALTY;
};
