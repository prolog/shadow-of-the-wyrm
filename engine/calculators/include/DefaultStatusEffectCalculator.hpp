#pragma once
#include "StatusEffectCalculator.hpp"
#include "Creature.hpp"

class DefaultStatusEffectCalculator : public StatusEffectCalculator
{
  public:
    virtual ~DefaultStatusEffectCalculator() = default;

    int calculate_pct_chance_effect(CreaturePtr creature) const override;
    int calculate_duration_in_minutes(CreaturePtr creature) const override;
};

