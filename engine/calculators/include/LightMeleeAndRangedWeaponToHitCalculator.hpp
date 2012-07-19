#pragma once
#include "ToHitCalculator.hpp"

class LightMeleeAndRangedWeaponToHitCalculator : public ToHitCalculator
{
  public:
    LightMeleeAndRangedWeaponToHitCalculator();
    LightMeleeAndRangedWeaponToHitCalculator(const AttackType attack_type);
    
    int calculate(CreaturePtr creature);
    
  protected:
    int get_combat_or_archery_bonus(CreaturePtr creature) const;
};
