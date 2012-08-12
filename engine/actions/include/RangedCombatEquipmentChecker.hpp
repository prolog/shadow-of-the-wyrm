#pragma once
#include <string>
#include <utility>
#include "Creature.hpp"

class RangedCombatEquipmentChecker
{
  public:
    std::pair<bool, std::string> can_creature_do_ranged_combat(CreaturePtr creature);

  protected:
    bool is_ranged_weapon_equipped(CreaturePtr creature);
    std::string get_ranged_weapon_not_equipped_message() const;

    bool is_ranged_weapon_and_ammunition_equipped(CreaturePtr creature);
    std::string get_ammunition_not_equipped_message() const;

    bool does_ranged_weapon_match_ammunition(CreaturePtr creature);
    std::string get_weapon_and_ammunition_mismatch_message() const;
};
