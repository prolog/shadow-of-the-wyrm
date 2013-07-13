#pragma once
#include "IStatusEffectCalculator.hpp"
#include "Creature.hpp"

// Class used to determine whether a creature is muted, and for how long.
class MutenessCalculator : public IStatusEffectCalculator
{
  public:
    int calculate_pct_chance_effect(CreaturePtr creature) const;
    int calculate_duration_in_minutes(CreaturePtr creature) const;

  protected:
    int calculate_muteness_duration_mean(CreaturePtr creature) const;

    static const int BASE_MUTENESS_DURATION_MEAN;
    static const int BASE_MUTENESS_PCT_CHANCE;
    static const int BASE_MUTENESS_CHANCE_CHARISMA_MODIFIER;
};

