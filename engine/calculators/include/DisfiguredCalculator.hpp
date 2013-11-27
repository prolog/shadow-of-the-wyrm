#pragma once
#include "IStatusEffectCalculator.hpp"
#include "Creature.hpp"

// Class used to determine whether a creature is disfigured (reduced
// statistics) as the result of an acid attack, and for how long.
class DisfiguredCalculator : public IStatusEffectCalculator
{
  public:
    int calculate_pct_chance_effect(CreaturePtr creature) const override;
    int calculate_duration_in_minutes(CreaturePtr creature) const override;

  protected:
    static const int BASE_DISFIGURED_DURATION_MEAN;
    static const int BASE_DISFIGURED_PCT_CHANCE;
    static const int BASE_DISFIGURED_CHANCE_HEALTH_MODIFIER;
};

