#pragma once
#include "StatusEffectCalculator.hpp"
#include "Creature.hpp"

// Class used to determine whether a creature is slowed (longer time
// between actions).
class SlownessCalculator : public StatusEffectCalculator
{
  public:
    virtual ~SlownessCalculator() = default;

    int calculate_pct_chance_effect(CreaturePtr creature) const override;
    int calculate_duration_in_minutes(CreaturePtr creature) const override;

  protected:
    static const int BASE_SLOWNESS_DURATION_MEAN;
    static const int BASE_SLOWNESS_PCT_CHANCE;
    static const int BASE_SLOWNESS_CHANCE_AGILITY_MODIFIER;
};

