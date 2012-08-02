#pragma once
#include "PhysicalDamageCalculator.hpp"

class RangedPhysicalDamageCalculator : public PhysicalDamageCalculator
{
  public:
    RangedPhysicalDamageCalculator();
    
    virtual int get_statistic_based_damage_modifier(CreaturePtr attacking_creature);
};
