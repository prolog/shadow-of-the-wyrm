#pragma once
#include <string>
#include "AttackTypes.hpp"
#include "EquipmentTypes.hpp"
#include "Weapon.hpp"

class EquipmentTextKeys
{
  public:
    static const std::string EQUIPMENT_HEAD;
    static const std::string EQUIPMENT_NECK;
    static const std::string EQUIPMENT_RIGHT_FINGER;
    static const std::string EQUIPMENT_LEFT_FINGER;
    static const std::string EQUIPMENT_WIELDED;
    static const std::string EQUIPMENT_OFF_HAND;
    static const std::string EQUIPMENT_BODY;
    static const std::string EQUIPMENT_AROUND_BODY;
    static const std::string EQUIPMENT_FEET;
    static const std::string EQUIPMENT_RANGED;
    static const std::string EQUIPMENT_AMMUNITION;
    static const std::string EQUIPMENT_RESISTS_FLAGS;
    static const std::string EQUIPMENT_WIELDED_UNSURE;
    static const std::string EQUIPMENT_REMOVAL_CURSED;
    
    static std::string get_equipment_text_from_given_worn_location(const EquipmentWornLocation& worn_location);
    static std::string get_ranged_weapon_synopsis(WeaponPtr ranged_weapon, WeaponPtr ammunition, const std::string& difficulty_speed_and_damage_synopsis);
    static std::string get_weapon_difficulty_speed_and_damage_synopsis(const int base_difficulty, const int total_difficulty, const int speed, const Damage& damage);
    static std::string get_melee_weapon_synopsis(const AttackType attack_type, WeaponPtr weapon, const int base_difficulty, const int total_difficulty, const int speed, const Damage& damage); // used by the W/R commands
    static std::string get_melee_weapon_synopsis(WeaponPtr weapon); // Used by the codex

  protected:
    EquipmentTextKeys();
    
    static const std::string EQUIPMENT_RANGED_SYNOPSIS;
    static const std::string EQUIPMENT_WEAPON_DIFFICULTY_SPEED_AND_DAMAGE_SYNOPSIS;
    static const std::string EQUIPMENT_PRIMARY_MELEE_DIFFICULTY_SPEED_AND_DAMAGE_SYNOPSIS;
    static const std::string EQUIPMENT_SECONDARY_MELEE_DIFFICULTY_SPEED_AND_DAMAGE_SYNOPSIS;
};
