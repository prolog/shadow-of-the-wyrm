#pragma once
#include "PhysicalAttackSpeedCalculator.hpp"

// Attack speed calculator for unarmed tertiary attacks - basically, kicking.
// These always take the same speed and always return false for
// has_weapon_equipped(creature).
class TertiaryUnarmedPhysicalAttackSpeedCalculator : public PhysicalAttackSpeedCalculator
{
  public:
    ActionCostValue calculate_weapon_speed(CreaturePtr creature) override;

  protected:
    bool has_weapon_equipped(CreaturePtr creature) override;
};

