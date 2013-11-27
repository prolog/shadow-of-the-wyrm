#pragma once
#include "IStatusEffectCalculator.hpp"
#include "Creature.hpp"

// A class used to calculate whether a creature gets poisoned, the duration
// of the poisoning, the damage, and other aspects of poison status
// effects.
class PoisonCalculator : public IStatusEffectCalculator
{
  public:
    int calculate_pct_chance_effect(CreaturePtr creature) const override;
    int calculate_damage_per_tick(CreaturePtr creature) const;
    int calculate_duration_in_minutes(CreaturePtr creature) const override;

  protected:
    int calculate_poison_duration_mean(CreaturePtr creature) const;

    static const int BASE_POISON_DURATION_MEAN;
    static const int BASE_POISON_PCT_CHANCE;
    static const int BASE_POISON_CHANCE_HEALTH_MODIFIER;
    static const int HEALTH_DIVISOR;
    static const int HEALTH_THRESHOLD_EXTRA_DAMAGE;
};

