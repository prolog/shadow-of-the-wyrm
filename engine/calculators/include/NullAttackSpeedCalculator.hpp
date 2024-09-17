#pragma once
#include "AttackSpeedCalculator.hpp"

class NullAttackSpeedCalculator : public AttackSpeedCalculator
{
  public:
    virtual ~NullAttackSpeedCalculator() = default;

    ActionCostValue calculate(CreaturePtr creature) override;
};
