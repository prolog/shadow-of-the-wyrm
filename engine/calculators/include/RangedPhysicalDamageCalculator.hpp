#pragma once
#include "PhysicalDamageCalculator.hpp"

class RangedPhysicalDamageCalculator : public PhysicalDamageCalculator
{
  public:
    RangedPhysicalDamageCalculator(const PhaseOfMoonType new_pom);
    
    virtual int get_statistic_based_damage_modifier(CreaturePtr attacking_creature) override;
};
