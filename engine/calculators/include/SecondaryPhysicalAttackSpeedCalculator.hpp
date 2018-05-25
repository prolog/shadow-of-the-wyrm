#pragma once
#include "PhysicalAttackSpeedCalculator.hpp"

class SecondaryPhysicalAttackSpeedCalculator : public PhysicalAttackSpeedCalculator
{
  public:
    ActionCostValue calculate_weapon_speed(CreaturePtr creature) override;

  protected:
    bool has_weapon_equipped(CreaturePtr creature);
    int calculate_speed_penalty(CreaturePtr creature);

    static const int BASE_SPEED_PENALTY;
};

