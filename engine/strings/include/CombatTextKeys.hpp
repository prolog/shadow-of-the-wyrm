#pragma once
#include <map>
#include <string>
#include <vector>
#include "Damage.hpp"

// Contains player and non-player versions of all combat strings.
class CombatTextKeys
{
  public:
    static std::string get_pierce_message(const bool attacker_is_player, const bool attacked_is_player, const std::string& attacker, const std::string& target);
    static std::string get_incorporeal_attack_message(const bool attacker_is_player, const bool attacked_is_player, const std::string& attacker, const std::string& target);
    static std::string get_vorpal_message(const bool attacker_is_player, const bool attacked_is_player, const std::string& attacker, const std::string& target);
    static std::string get_close_miss_message(const bool attacker_is_player, const bool attacked_is_player, const std::string& attacker, const std::string& missed_target);
    static std::string get_miss_message(const bool attacker_is_player, const bool attacked_is_player, const std::string& attacker, const std::string& missed_target);
    static std::string get_critical_hit_message();
    static std::string get_mighty_blow_message();
    static std::string get_hit_message(const bool attacker_is_player, const bool attacked_is_player, const DamageType damage_type, const std::string& attacker, const std::string& hit_target, const bool use_multiple_damage_type_msgs);
    static std::string get_monster_killed_message(const std::string& monster_name);
    static std::string get_monster_dies_message(const std::string& monster_name);
    static std::string get_no_damage_message(const bool target_is_player, const std::string& target);
    static std::string get_ranged_attack_message(const bool attacker_is_player, const bool attacked_is_player, const bool uses_launcher, const std::string& attacker, const std::string& ammunition, const std::string& target);

    static const std::string COMBAT_TARGET_TOO_FAR_AWAY;
    static const std::string COMBAT_CRITICAL_HIT_MESSAGE; // Common to both - no substitutions
    static const std::string COMBAT_MIGHTY_BLOW_MESSAGE; // Common to both - no substitutions
    static const std::string COMBAT_ATTACK_NO_EFFECT;

  protected:
    CombatTextKeys();

    static std::pair<std::string, std::string> get_appropriate_attacker_and_target(const bool attacker_is_player, const bool attacked_is_player, const std::string& non_blind_attacker, const std::string& non_blind_target);

    static const std::string COMBAT_MONSTER_RANGED_ATTACK_MESSAGE;
    static const std::string COMBAT_PLAYER_RANGED_ATTACK_MESSAGE;
    static const std::string COMBAT_MONSTER_RANGED_ATTACK_LAUNCHER_MESSAGE;
    static const std::string COMBAT_PLAYER_RANGED_ATTACK_LAUNCHER_MESSAGE;
    static const std::string COMBAT_MONSTER_RANGED_ATTACK_NO_TARGET_MESSAGE;
    static const std::string COMBAT_PLAYER_RANGED_ATTACK_NO_TARGET_MESSAGE;
    static const std::string COMBAT_MONSTER_RANGED_ATTACK_LAUNCHER_NO_TARGET_MESSAGE;
    static const std::string COMBAT_PLAYER_RANGED_ATTACK_LAUNCHER_NO_TARGET_MESSAGE;
    static const std::string COMBAT_MONSTER_NO_DAMAGE_RECEIVED_MESSAGE;
    static const std::string COMBAT_PLAYER_NO_DAMAGE_RECEIVED_MESSAGE;
    static const std::string COMBAT_MONSTER_KILLED_MESSAGE;
    static const std::string COMBAT_MONSTER_DIES_MESSAGE;
    static const std::string COMBAT_MONSTER_KILLED_OR_DIES_MESSAGE_PLAYER_BLIND;
    static const std::string COMBAT_CLOSE_MISS_MESSAGE;
    static const std::string COMBAT_CLOSE_MISS_MESSAGE_NP;
    static const std::string COMBAT_MISS_MESSAGE;
    static const std::string COMBAT_MISS_MESSAGE_NP;
    static const std::string COMBAT_PIERCE_MESSAGE;
    static const std::string COMBAT_PIERCE_MESSAGE_NP;
    static const std::string COMBAT_VORPAL_MESSAGE;
    static const std::string COMBAT_VORPAL_MESSAGE_NP;
    static const std::string COMBAT_INCORPOREAL_MESSAGE;
    static const std::string COMBAT_INCORPOREAL_MESSAGE_NP;
    
    static void populate_combat_messages();
    static std::string create_key(const bool is_player, const DamageType damage_type);
    static std::map<std::string, std::vector<std::string>> combat_damage_hit_messages;
};

