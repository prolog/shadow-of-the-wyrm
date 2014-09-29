#pragma once
#include "IPhysicalAttackSpeedCalculator.hpp"

// Attack speed calculator for unarmed tertiary attacks - basically, kicking.
// These always take the same speed and always return false for
// has_weapon_equipped(creature).
class TertiaryUnarmedPhysicalAttackSpeedCalculator : public IPhysicalAttackSpeedCalculator
{
  public:
    ActionCostValue calculate_weapon_speed(CreaturePtr creature) override;

  protected:
    bool has_weapon_equipped(CreaturePtr creature) override;
};

