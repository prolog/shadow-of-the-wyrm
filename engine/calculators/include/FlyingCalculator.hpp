#pragma once
#include "StatusEffectCalculator.hpp"
#include "Creature.hpp"

class FlyingCalculator : public StatusEffectCalculator
{
  public:
    int calculate_pct_chance_effect(CreaturePtr creature) const override;
    int calculate_duration_in_minutes(CreaturePtr creature) const override;

  protected:
    static const int BASE_FLYING_DURATION_MEAN;
    static const int BASE_FLYING_PCT_CHANCE;
};

