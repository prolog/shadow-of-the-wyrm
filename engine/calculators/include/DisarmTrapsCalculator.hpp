#pragma once
#include "Creature.hpp"

enum struct DisarmTrapsOutcome
{
  DISARM_TRAPS_TRIGGER = 0,
  DISARM_TRAPS_FAIL = 1,
  DISARM_TRAPS_DISARM = 2,
  DISARM_TRAPS_DISMANTLE = 3
};

class DisarmTrapsCalculator
{
  public:
    DisarmTrapsOutcome calculate_disarm_traps_outcome(CreaturePtr creature, const bool has_component_items);

  protected:
    static const float DISARM_TRAPS_SKILL_MULTIPLIER;
    static const float DISMANTLE_TRAPS_SKILL_MULTIPLIER;
};

