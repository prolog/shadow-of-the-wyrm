#pragma once
#include "ISpeedCalculator.hpp"

class NullSpeedCalculator : public ISpeedCalculator
{
  public:
    ActionCostValue calculate(CreaturePtr creature) override;
};
