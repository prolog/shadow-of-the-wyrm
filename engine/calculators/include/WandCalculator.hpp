#pragma once
#include "Creature.hpp"
#include "Wand.hpp"

class WandCalculator
{
  public:
    std::pair<int,int> calc_x_in_y_chance_explode(CreaturePtr creature, ItemPtr wand);
    int calc_explosion_damage(WandPtr wand);
    int calc_damage_bonus(CreaturePtr creature);
    int calc_pct_chance_free_charge(CreaturePtr creature);
    int calc_spell_castings_per_charge(CreaturePtr creature);
    int calc_num_charges(CreaturePtr creature);

    int calc_max_recharge_charges(CreaturePtr creature, const ItemStatus recharge_status);

  protected:
    static const int DAMAGE_BONUS_STAT_DIVISOR;
    static const int DAMAGE_BONUS_SKILL_DIVISOR;
    static const int FREE_CHARGE_SKILL_DIVISOR;
    static const int DEFAULT_SPELL_CASTINGS_PER_CHARGE;
    static const int MIN_SPELL_CASTINGS_PER_CHARGE;
    static const int NUM_CHARGE_DIVISOR;
    static const int WANDCRAFT_RECHARGE_DIVISOR;
    static const int BASE_PCT_CHANCE_EXPLODE_CURSED;
    static const int WANDCRAFT_THRESHOLD_CAN_EXPLODE;
};

