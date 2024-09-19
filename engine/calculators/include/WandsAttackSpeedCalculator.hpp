#pragma once
#include "AttackSpeedCalculator.hpp"

class WandsAttackSpeedCalculator : public AttackSpeedCalculator
{
  public:
    virtual ~WandsAttackSpeedCalculator() = default;

    ActionCostValue calculate(CreaturePtr creature) override;

  protected:
    static const int WANDCRAFT_SPEED_DIVISOR;
};

