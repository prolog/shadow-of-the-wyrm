#pragma once
#include "Creature.hpp"

class ToHitCalculator
{
  public:
    virtual int calculate(CreaturePtr creature) = 0;
};

typedef boost::shared_ptr<ToHitCalculator> ToHitCalculatorPtr;
