#pragma once
#include "AttackTypes.hpp"
#include "Creature.hpp"
#include "Damage.hpp"
#include "DamageTypes.hpp"

class CombatManager
{
  public:
    friend class SL_Engine_Combat_CombatManager;

    CombatManager();
    
    // JCD FIXME make this ActionCost later
    bool attack(CreaturePtr attacking_creature, CreaturePtr attacked_creature);
    
  protected:
    
    // Functions to handle the attacking mechanics and add messages as necessary.
    bool hit(CreaturePtr attacking_creature, CreaturePtr attacked_creature, const int d100_roll, const Damage& damage, const AttackType attack_type);
    bool miss(CreaturePtr attacking_creature, CreaturePtr attacked_creature);
    bool close_miss(CreaturePtr attacking_creature, CreaturePtr attacked_creature);
    
    void deal_damage(CreaturePtr attacked_creature, const int damage_dealt);
    
    void add_any_necessary_damage_messages(const int damage);
    void add_combat_message(const std::string& message);
    void send_combat_messages();
    
    // JCD FIXME NOT IMPLEMENTED FULLY:
    // Functions to determine whether a particular attack hits, misses, etc.
    bool is_critical_hit(const int d100_roll);
    bool is_mighty_blow(const int d100_roll);
    bool is_hit(const int total_roll, const int target_number_value);
    bool is_miss(const int total_roll, const int target_number_value);
    bool is_close_miss(const int total_roll, const int target_number_value);
    bool is_automatic_miss(const int d100_roll);
};
