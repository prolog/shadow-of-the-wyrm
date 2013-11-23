#pragma once
#include <memory>
#include "ActionCost.hpp"
#include "Creature.hpp"

class ISpeedCalculator
{
  public:
    virtual ActionCostValue calculate(CreaturePtr creature) = 0;
};

typedef std::shared_ptr<ISpeedCalculator> ISpeedCalculatorPtr;

