#pragma once
#include "ISpeedCalculator.hpp"

class MagicalAttackSpeedCalculator : public ISpeedCalculator
{
  public:
    ActionCostValue calculate(CreaturePtr creature);
};

