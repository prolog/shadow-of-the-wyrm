#pragma once
#include "Creature.hpp"

class CombatEffectsCalculator
{
  public:
    int calc_pct_chance_counter_strike(CreaturePtr creature) const;

  protected:
    static const int COMBAT_SKILL_DIVISOR;
    static const int DEXTERITY_DIVISOR;
};

