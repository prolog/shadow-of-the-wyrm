#pragma once
#include "Creature.hpp"
#include "Door.hpp"
#include "MaterialTypes.hpp"

class DoorBreakageCalculator
{
  public:
    DoorBreakageCalculator();
    int calculate_pct_chance_breakage(CreaturePtr creature, DoorPtr door);

  protected:
    int get_base_strength_value(const MaterialType mt);

    const std::map<MaterialType, int> material_base_strength_values;
    static const int DEFAULT_STR_BASE;
    static const int STR_INCR_DIVISOR;
};

