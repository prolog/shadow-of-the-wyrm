#pragma once
#include "Creature.hpp"

class CreatureCalculator
{
  public:
    static void update_calculated_values(const CreaturePtr& c);

  protected:
    CreatureCalculator();
    ~CreatureCalculator();
};
