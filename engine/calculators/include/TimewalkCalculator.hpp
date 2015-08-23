#pragma once
#include "StatusEffectCalculator.hpp"
#include "Creature.hpp"

class TimewalkCalculator : public StatusEffectCalculator
{
  public:
    int calculate_pct_chance_effect(CreaturePtr creature) const override;
    int calculate_duration_in_minutes(CreaturePtr creature) const override;
    int calculate_pct_chance_wear_off_per_turn(CreaturePtr creature) const;

  protected:
    static const int BASE_TIMEWALK_PCT_CHANCE;
    static const int BASE_TIMEWALK_WEAR_OFF_CHANCE_PER_TURN;
};

