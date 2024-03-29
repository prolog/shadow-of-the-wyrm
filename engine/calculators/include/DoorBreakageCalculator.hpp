#pragma once
#include "Creature.hpp"
#include "Features.hpp"
#include "MaterialTypes.hpp"

class DoorBreakageCalculator
{
  public:
    DoorBreakageCalculator();
    int calculate_pct_chance_breakage(CreaturePtr creature, EntrancePtr entr);

  protected:
    int get_base_strength_value(EntrancePtr entr);

    const std::map<MaterialType, int> material_base_strength_values;
    static const int DEFAULT_STR_BASE;
    static const int DEFAULT_STR_LOCK;
    static const int STR_INCR_DIVISOR;
};

