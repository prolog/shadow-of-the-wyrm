#pragma once
#include "Creature.hpp"

class SoakCalculator
{
  public:
    static int calculate_soak(const CreaturePtr& c);

  protected:
    static int get_equipment_bonus(const CreaturePtr& c);
    
    SoakCalculator();
    ~SoakCalculator();
};
