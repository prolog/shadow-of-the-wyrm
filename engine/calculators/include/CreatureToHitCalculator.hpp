#pragma once
#include "Creature.hpp"

// Class that calculates the base to-hit for a creature (based on
// equipment, current ongoing spells, etc).
class CreatureToHitCalculator
{
  public:
    int calculate_to_hit(CreaturePtr c);

  protected:
    int get_equipment_bonus(CreaturePtr c);
};
