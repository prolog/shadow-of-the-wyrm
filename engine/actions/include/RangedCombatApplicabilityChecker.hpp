#pragma once
#include <string>
#include <utility>
#include "Creature.hpp"

class RangedCombatApplicabilityChecker
{
  public:
    std::pair<bool, std::string> can_creature_do_ranged_combat(CreaturePtr creature);

    bool is_ranged_weapon_equipped(CreaturePtr creature);
    bool is_ammunition_cursed(CreaturePtr creature);
    bool is_ranged_weapon_and_ammunition_equipped(CreaturePtr creature);
    bool does_ranged_weapon_match_ammunition(CreaturePtr creature);
    bool is_ranged_weapon_required_and_equipped(CreaturePtr creature);

  protected:
    bool is_current_map_type_not_world();

    std::string get_ranged_combat_on_world_map_not_allowed_message() const;    
    std::string get_ranged_weapon_not_equipped_message() const;
    std::string get_ammunition_cursed_message() const;
    std::string get_ammunition_not_equipped_message() const;
    std::string get_weapon_and_ammunition_mismatch_message() const;
    std::string get_ammunition_requires_ranged_weapon_message() const;

    std::string get_overburdened_message() const;
};

