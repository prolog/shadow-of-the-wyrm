#pragma once
#include "DamageTypes.hpp"
#include "StatusEffect.hpp"

// StatusEffectFactory creates StatusEffectPtrs for various status buffs/
// ailments based on the string identifier.  The identifiers correspond
// to those in world/include/StatusTypes.hpp, in class StatusIdentifier.
class StatusEffectFactory
{
  public:
    static StatusEffectPtr create_effect_for_damage_type(const DamageType damage_type);
    static StatusEffectPtr create_status_change(const std::string& status_identifier);

  protected:
    StatusEffectFactory();
    ~StatusEffectFactory();
};

