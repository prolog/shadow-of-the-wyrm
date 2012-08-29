#pragma once
#include "IPhysicalAttackSpeedCalculator.hpp"

class PrimaryPhysicalAttackSpeedCalculator : public IPhysicalAttackSpeedCalculator
{
  public:
    ActionCostValue calculate_weapon_speed(CreaturePtr creature);

  protected:
    bool has_weapon_equipped(CreaturePtr creature);
};

