#pragma once
#include "ActionCost.hpp"
#include "AttackTypes.hpp"
#include "Creature.hpp"
#include "Damage.hpp"
#include "DamageTypes.hpp"
#include "StatusEffect.hpp"

class CombatManager
{
  public:
    friend class SL_Engine_Combat_CombatManager;

    CombatManager();
    bool operator==(const CombatManager& cm) const;
    
    ActionCostValue attack(CreaturePtr creature, const Direction d);
    ActionCostValue attack(CreaturePtr attacking_creature, 
                           CreaturePtr attacked_creature, 
                           const AttackType = AttackType::ATTACK_TYPE_MELEE_PRIMARY, 
                           const bool mark_skills = true, 
                           DamagePtr damage = DamagePtr());

    void deal_damage(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const int damage_dealt, const std::string combat_message = "");
    void handle_damage_effects(CreaturePtr attacked_creature, const int damage_dealt, const DamageType damage_type, const int effect_bonus, const StatusAilments& status_ailments);

  protected:
    // Apply a particular status effect.
    void apply_damage_effect(CreaturePtr creature, StatusEffectPtr status_effect, const int effect_bonus);
    
    // Functions to handle the attacking mechanics and add messages as necessary.
    bool hit(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const int d100_roll, const Damage& damage, const AttackType attack_type);
    bool miss(CreaturePtr attacking_creature, CreaturePtr attacked_creature);
    bool close_miss(CreaturePtr attacking_creature, CreaturePtr attacked_creature);
        
    bool run_attack_script_if_necessary(CreaturePtr creature, CreaturePtr attacked_creature);
    void add_any_necessary_damage_messages(CreaturePtr creature, CreaturePtr attacked_creature, const int damage, const bool piercing, const bool incorporeal);
    void add_combat_message(CreaturePtr creature, CreaturePtr attacked_creature, const std::string& message);
    void send_combat_messages(CreaturePtr creature);
    
    // Functions to determine whether a particular attack hits, misses, etc.
    bool is_hit(const int total_roll, const int target_number_value);
    bool is_miss(const int total_roll, const int target_number_value);
    bool is_close_miss(const int total_roll, const int target_number_value);
    bool is_automatic_miss(const int d100_roll);

    bool does_attack_slay_creature_race(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const AttackType attack_type);
    
    void mark_appropriate_skills(CreaturePtr attacking_creature, const AttackType attack_type, const bool attack_success);
    
    // Update the mortuary on the game and on the attacking creature.
    void update_mortuaries(CreaturePtr attacking_creature, const std::string& killed_creature_id);

    // Get the appropriate description for the defending creature.
    std::string get_appropriate_creature_description(CreaturePtr attacking_creature, CreaturePtr creature);
};
