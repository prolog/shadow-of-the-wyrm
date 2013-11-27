#pragma once
#include "IStatusEffectCalculator.hpp"
#include "Creature.hpp"

class HasteCalculator : public IStatusEffectCalculator
{
  public:
    int calculate_pct_chance_effect(CreaturePtr creature) const override;
    int calculate_duration_in_minutes(CreaturePtr creature) const override;

  protected:
    static const int BASE_HASTE_DURATION_MEAN;
    static const int BASE_HASTE_PCT_CHANCE;
};

