#pragma once
#include "Creature.hpp"

class PrimordialCalculator
{
  public:
    int get_max_skill_castings(CreaturePtr creature);
  
  protected:
    static const int SKILL_CASTINGS_DIVISOR;
};

