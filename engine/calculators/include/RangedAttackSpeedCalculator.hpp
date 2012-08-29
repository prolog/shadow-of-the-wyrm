#pragma once
#include "ISpeedCalculator.hpp"

class RangedAttackSpeedCalculator : public ISpeedCalculator
{
  public:
    ActionCostValue calculate(CreaturePtr creature);
};
