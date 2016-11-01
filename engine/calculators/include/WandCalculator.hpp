#pragma once
#include "Creature.hpp"

class WandCalculator
{
  public:
    int calc_damage_bonus(CreaturePtr creature);
    int calc_pct_chance_free_charge(CreaturePtr creature);
    int calc_spell_castings_per_charge(CreaturePtr creature);
    int calc_num_charges(CreaturePtr creature);

  protected:
    static const int DAMAGE_BONUS_STAT_DIVISOR;
    static const int DAMAGE_BONUS_SKILL_DIVISOR;
    static const int FREE_CHARGE_SKILL_DIVISOR;
    static const int DEFAULT_SPELL_CASTINGS_PER_CHARGE;
    static const int MIN_SPELL_CASTINGS_PER_CHARGE;
    static const int NUM_CHARGE_DIVISOR;
};

