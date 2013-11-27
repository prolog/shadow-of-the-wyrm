#pragma once
#include "IStatusEffectCalculator.hpp"
#include "Creature.hpp"

// Class used to determine whether a creature is paralyzed (can't take
// any actions - turn skipped) and if so, for how long.
class ParalysisCalculator : public IStatusEffectCalculator
{
  public:
    int calculate_pct_chance_effect(CreaturePtr creature) const override;
    int calculate_duration_in_minutes(CreaturePtr creature) const override;

  protected:
    static const int BASE_PARALYSIS_DURATION_MEAN;
    static const int BASE_PARALYSIS_PCT_CHANCE;
    static const int BASE_PARALYSIS_CHANCE_HEALTH_MODIFIER;
};

