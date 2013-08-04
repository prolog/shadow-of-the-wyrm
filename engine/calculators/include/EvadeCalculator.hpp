#pragma once
#include "Creature.hpp"

class EvadeCalculator
{
  public:
    static int calculate_evade(const CreaturePtr& c);

  protected:
    static int get_equipment_bonus(const CreaturePtr& c);
    static int get_status_bonus(const CreaturePtr& c);
    
    EvadeCalculator();
    ~EvadeCalculator();
};
