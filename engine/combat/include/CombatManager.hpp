#pragma once
#include <boost/make_shared.hpp>
#include "ActionCost.hpp"
#include "AttackTypes.hpp"
#include "Creature.hpp"
#include "Damage.hpp"
#include "DamageTypes.hpp"

class CombatManager
{
  public:
    friend class SL_Engine_Combat_CombatManager;

    CombatManager();
    bool operator==(const CombatManager& cm) const;
    
    ActionCostValue attack(CreaturePtr creature, const Direction d);
    ActionCostValue attack(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const AttackType = ATTACK_TYPE_MELEE_PRIMARY, const bool mark_skills = true, DamagePtr damage = DamagePtr());

    void deal_damage(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const int damage_dealt, const std::string combat_message = "");
    void handle_damage_effects(CreaturePtr attacked_creature, const int damage_dealt, const DamageType damage_type);

  protected:
    
    // Functions to handle the attacking mechanics and add messages as necessary.
    bool hit(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const int d100_roll, const Damage& damage, const AttackType attack_type);
    bool miss(CreaturePtr attacking_creature, CreaturePtr attacked_creature);
    bool close_miss(CreaturePtr attacking_creature, CreaturePtr attacked_creature);
        
    void add_any_necessary_damage_messages(CreaturePtr creature, const int damage);
    void add_combat_message(CreaturePtr creature, const std::string& message);
    void send_combat_messages(CreaturePtr creature);
    
    // Functions to determine whether a particular attack hits, misses, etc.
    bool is_critical_hit(const int d100_roll);
    bool is_mighty_blow(const int d100_roll);
    bool is_hit(const int total_roll, const int target_number_value);
    bool is_miss(const int total_roll, const int target_number_value);
    bool is_close_miss(const int total_roll, const int target_number_value);
    bool is_automatic_miss(const int d100_roll);
    
    void mark_appropriate_skills(CreaturePtr attacking_creature, const AttackType attack_type, const bool attack_success);
    
    // Update the mortuary on the game and on the attacking creature.
    void update_mortuaries(CreaturePtr attacking_creature, const std::string& killed_creature_id);

    void run_death_event(CreaturePtr attacking_creature, CreaturePtr attacked_creature, MapPtr map);

    std::string get_appropriate_creature_description(CreaturePtr creature);
};
