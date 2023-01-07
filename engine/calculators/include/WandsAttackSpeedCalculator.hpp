#pragma once
#include "AttackSpeedCalculator.hpp"

class WandsAttackSpeedCalculator : public AttackSpeedCalculator
{
  public:
    ActionCostValue calculate(CreaturePtr creature) override;

  protected:
    static const int WANDCRAFT_SPEED_DIVISOR;
};

