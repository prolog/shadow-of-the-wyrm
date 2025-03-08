#pragma once
#include "StatusEffectCalculator.hpp"
#include "Creature.hpp"

class WaterBreathingCalculator : public StatusEffectCalculator
{
  public:
    virtual ~WaterBreathingCalculator() = default;
    int calculate_pct_chance_effect(CreaturePtr creature) const override;
    int calculate_duration_in_minutes(CreaturePtr creature) const override;

  protected:
    static const int WB_DURATION;
    static const int BASE_WB_PCT_CHANCE;
};

