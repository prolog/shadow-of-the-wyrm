#pragma once
#include "IPhysicalAttackSpeedCalculator.hpp"

class SecondaryPhysicalAttackSpeedCalculator : public IPhysicalAttackSpeedCalculator
{
  public:
    ActionCostValue calculate_weapon_speed(CreaturePtr creature) override;

  protected:
    bool has_weapon_equipped(CreaturePtr creature);
};

