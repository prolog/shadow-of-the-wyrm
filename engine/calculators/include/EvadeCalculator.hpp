#pragma once
#include "Creature.hpp"

class EvadeCalculator
{
  public:
    static int calculate_evade(const CreaturePtr& c);

  protected:
    EvadeCalculator();
    ~EvadeCalculator();
};
