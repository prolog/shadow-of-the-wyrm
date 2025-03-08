#pragma once
#include "StatusEffectCalculator.hpp"
#include "Creature.hpp"

class RageCalculator : public StatusEffectCalculator
{
  public:
    virtual ~RageCalculator() = default;

    int calculate_duration_in_minutes(CreaturePtr creature) const override;

  protected:
    int calculate_pct_chance_effect(CreaturePtr creature) const override;

    static const int BASE_RAGE_DURATION_MEAN;
};

