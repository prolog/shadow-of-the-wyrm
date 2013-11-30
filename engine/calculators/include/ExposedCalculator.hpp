#pragma once
#include "StatusEffectCalculator.hpp"
#include "Creature.hpp"

// Class used to determine whether a creature is more exposed to incoming
// attacks as the result of being stabbed, and for how long.
class ExposedCalculator : public StatusEffectCalculator
{
  public:
    int calculate_pct_chance_effect(CreaturePtr creature) const override;
    int calculate_duration_in_minutes(CreaturePtr creature) const override;

  protected:
    static const int BASE_EXPOSED_DURATION_MEAN;
    static const int BASE_EXPOSED_PCT_CHANCE;
    static const int BASE_EXPOSED_CHANCE_AGILITY_MODIFIER;
};

