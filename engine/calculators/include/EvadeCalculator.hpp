#pragma once
#include "Creature.hpp"

class EvadeCalculator
{
  public:
    static int calculate_evade(const CreaturePtr& c);

  protected:
    static int get_equipment_bonus(const CreaturePtr& c);
    static int get_modifier_bonus(const CreaturePtr& c);
    static int get_skill_bonus(const CreaturePtr& c);
    static int get_hide_bonus(const CreaturePtr& c);
    static int get_rage_penalty(const CreaturePtr& c);
    
    EvadeCalculator();
    ~EvadeCalculator();
};
