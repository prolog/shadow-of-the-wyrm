#pragma once
#include "StatusEffectCalculator.hpp"
#include "Creature.hpp"

// Class used to determine whether a creature is bloodied by a slash, and
// for how long.
class BloodiedCalculator : public StatusEffectCalculator
{
  public:
    int calculate_pct_chance_effect(CreaturePtr creature) const override;
    int calculate_duration_in_minutes(CreaturePtr creature) const override;

  protected:
    static const int BASE_BLOODIED_DURATION_MEAN;
    static const int BASE_BLOODIED_PCT_CHANCE;
    static const int BASE_BLOODIED_CHANCE_STRENGTH_MODIFIER;
};

