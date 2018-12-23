#pragma once
#include "ActionCost.hpp"
#include "AttackTypes.hpp"
#include "Creature.hpp"
#include "Damage.hpp"
#include "DamageTypes.hpp"
#include "StatusEffect.hpp"

class Game;

class CombatManager
{
  public:
    friend class SW_Engine_Combat_CombatManager;

    CombatManager();
    bool operator==(const CombatManager& cm) const;
    
    // Convenient function
    ActionCostValue attack(CreaturePtr creature, const Direction d);

    // The "real" attack function
    ActionCostValue attack(CreaturePtr attacking_creature, 
                           CreaturePtr attacked_creature, 
                           const AttackType = AttackType::ATTACK_TYPE_MELEE_PRIMARY, 
                           const AttackSequenceType = AttackSequenceType::ATTACK_SEQUENCE_INITIAL,
                           const bool mark_skills = true, 
                           DamagePtr damage = DamagePtr());

    void deal_damage(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const std::string& source_id, const int damage_dealt, const Damage& damage, const std::string combat_message_sid = "");
    void handle_damage_effects(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const int damage_dealt, const DamageType damage_type, const int effect_bonus, const StatusAilments& status_ailments, const int danger_level);

  protected:
    // Apply a particular status effect.
    void apply_damage_effect(CreaturePtr creature, StatusEffectPtr status_effect, const int effect_bonus, const int danger_level);

    // Handle vorpal and other damage flags as necessary
    void handle_vorpal_if_necessary(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const Damage& damage_info, int& damage_dealt);
    void handle_draining_if_necessary(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const int damage_dealt, const Damage& damage_info);
    void handle_ethereal_if_necessary(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const int damage_dealt, const Damage& damage_info);
    void handle_explosive_if_necessary(CreaturePtr attacking_creature, CreaturePtr attacked_creature, MapPtr current_map, const int damage_dealt, const Damage& damage_info, const AttackType attack_type);

    // Can the creature split when hit?
    void handle_split_if_necessary(CreaturePtr attacking_creature, CreaturePtr attacked_creature, RacePtr creature_race, MapPtr current_map);

    // Set the creature to hostile, and yell out for support.
    void handle_hostility_implications(CreaturePtr attacking_creature, CreaturePtr attacked_creature);
    
    // Functions to handle the attacking mechanics and add messages as necessary.
    //
    // These are generally not called directly, other than via the Lua API.

    // ::hit returns the actual damage dealt, which is needed in some cases
    // (for example, to determine whether skills should be improved).
    int hit(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const int d100_roll, const Damage& damage, const AttackType attack_type, const AttackSequenceType ast);
    bool miss(CreaturePtr attacking_creature, CreaturePtr attacked_creature);
    bool close_miss(CreaturePtr attacking_creature, CreaturePtr attacked_creature);
    bool intimidate(CreaturePtr attacking_creature, CreaturePtr attacked_creature);
        
    bool run_attack_script_if_necessary(CreaturePtr creature, CreaturePtr attacked_creature);
    void add_any_necessary_damage_messages(CreaturePtr creature, CreaturePtr attacked_creature, const int damage, const bool piercing, const bool incorporeal);
    void add_combat_message(CreaturePtr creature, CreaturePtr attacked_creature, const std::string& message);
    void send_combat_messages(CreaturePtr creature);
    
    // Functions to determine whether a particular attack hits, misses, etc.
    bool is_hit(const int total_roll, const int target_number_value);
    bool is_miss(const int total_roll, const int target_number_value);
    bool is_intimidate(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const AttackType attack_type);
    bool is_close_miss(const int total_roll, const int target_number_value);
    bool is_automatic_miss(const int d100_roll);
    bool is_automatic_hit(const int d100_roll);

    bool destroy_weapon_if_necessary(CreaturePtr creature, const AttackType attack_type);

    bool counter_strike_if_necessary(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const AttackSequenceType ast);
    void add_counter_strike_message(CreaturePtr attacking_creature, CreaturePtr attacked_creature);
    bool handle_scything_if_necessary(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const AttackType attack_type, const AttackSequenceType ast, const Damage& damage_info);

    bool does_attack_slay_creature_race(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const AttackType attack_type);
    
    void mark_appropriately(CreaturePtr attacking_creature, const AttackType attack_type, Statistic& marked_statistic, const bool attack_success);
    void mark_health_for_damage_taken(CreaturePtr attacking_creature, CreaturePtr attacked_creature);
    bool knock_back_creature_if_necessary(const AttackType attack_type, CreaturePtr attacking_creature, CreaturePtr attacked_creature, Game& game, MapPtr current_map);
    
    // Update the mortuary on the game and on the attacking creature.
    void update_mortuaries(CreaturePtr attacking_creature, CreaturePtr attacked_creature);

    // Get the appropriate description for the defending creature.
    std::string get_appropriate_creature_description(CreaturePtr attacking_creature, CreaturePtr creature);

    static const int PCT_CHANCE_MARK_STATISTIC_ON_MISS;
};
