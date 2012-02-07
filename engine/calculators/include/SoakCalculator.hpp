#pragma once
#include "Creature.hpp"

class SoakCalculator
{
  public:
    static int calculate_soak(const CreaturePtr& c);

  protected:
    SoakCalculator();
    ~SoakCalculator();
};
