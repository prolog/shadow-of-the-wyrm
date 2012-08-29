#pragma once
#include <boost/shared_ptr.hpp>
#include "ActionCost.hpp"
#include "Creature.hpp"

class ISpeedCalculator
{
  public:
    virtual ActionCostValue calculate(CreaturePtr creature) = 0;
};

typedef boost::shared_ptr<ISpeedCalculator> ISpeedCalculatorPtr;

