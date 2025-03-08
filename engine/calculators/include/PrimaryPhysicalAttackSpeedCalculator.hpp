#pragma once
#include "PhysicalAttackSpeedCalculator.hpp"

class PrimaryPhysicalAttackSpeedCalculator : public PhysicalAttackSpeedCalculator
{
  public:
    virtual ~PrimaryPhysicalAttackSpeedCalculator() = default;

    ActionCostValue calculate_weapon_speed(CreaturePtr creature) override;

  protected:
    bool has_weapon_equipped(CreaturePtr creature);
};

