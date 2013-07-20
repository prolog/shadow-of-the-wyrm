#pragma once
#include "IStatusEffectCalculator.hpp"
#include "Creature.hpp"

// Class used to determine whether a creature is slowed (longer time
// between actions).
class SlownessCalculator : public IStatusEffectCalculator
{
  public:
    int calculate_pct_chance_effect(CreaturePtr creature) const;
    int calculate_duration_in_minutes(CreaturePtr creature) const;

  protected:
    static const int BASE_SLOWNESS_DURATION_MEAN;
    static const int BASE_SLOWNESS_PCT_CHANCE;
    static const int BASE_SLOWNESS_CHANCE_AGILITY_MODIFIER;
};

