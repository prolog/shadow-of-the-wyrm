#pragma once
#include <memory>
#include "ActionCost.hpp"
#include "Creature.hpp"

class ISpeedCalculator
{
  public:
    virtual ActionCostValue calculate(CreaturePtr creature) = 0;
};

using ISpeedCalculatorPtr = std::shared_ptr<ISpeedCalculator>;

