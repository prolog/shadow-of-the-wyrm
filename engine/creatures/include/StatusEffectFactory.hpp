#pragma once
#include "Creature.hpp"
#include "DamageTypes.hpp"
#include "StatusEffect.hpp"

// StatusEffectFactory creates StatusEffectPtrs for various status buffs/
// ailments based on the string identifier.  The identifiers correspond
// to those in world/include/StatusTypes.hpp, in class StatusIdentifier.
class StatusEffectFactory
{
  public:
    static std::string get_status_identifier_for_damage_type(const DamageType dt);

    static StatusEffectPtr create_effect_for_damage_type(CreaturePtr initiating_creature, const DamageType damage_type, const std::string& source_id);
    static StatusEffectPtr create_status_effect(CreaturePtr initiating_creature, const std::string& status_identifier, const std::string& source_id);

  protected:
    StatusEffectFactory();
    ~StatusEffectFactory();

    static void initialize_damage_status_ailments();

    static std::map<DamageType, std::string> damage_status_ailments;
};

