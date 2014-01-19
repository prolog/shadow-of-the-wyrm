#pragma once
#include "Creature.hpp"

// Class that calculates the additional damage for a creature, for example,
// based on equipment and spells.
class CreatureAdditionalDamageCalculator
{
  public:
    int calculate_additional_damage(CreaturePtr c);

  protected:
    int get_equipment_bonus(CreaturePtr c);
};

