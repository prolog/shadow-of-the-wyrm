#pragma once
#include "IStatusEffectCalculator.hpp"
#include "Creature.hpp"

// Class used to determine whether a creature is more exposed to incoming
// attacks as the result of being stabbed, and for how long.
class ExposedCalculator : public IStatusEffectCalculator
{
  public:
    int calculate_pct_chance_effect(CreaturePtr creature) const;
    int calculate_duration_in_minutes(CreaturePtr creature) const;

  protected:
    static const int BASE_EXPOSED_DURATION_MEAN;
    static const int BASE_EXPOSED_PCT_CHANCE;
    static const int BASE_EXPOSED_CHANCE_AGILITY_MODIFIER;
};

