#pragma once
#include "Creature.hpp"

class WandCalculator
{
  public:
    int calc_damage_bonus(CreaturePtr creature);
    int calc_pct_chance_free_charge(CreaturePtr creature);

  protected:
    static const int DAMAGE_BONUS_STAT_DIVISOR;
    static const int DAMAGE_BONUS_SKILL_DIVISOR;
    static const int FREE_CHARGE_SKILL_DIVISOR;
};

