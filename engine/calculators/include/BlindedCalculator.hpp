#pragma once
#include "StatusEffectCalculator.hpp"
#include "Creature.hpp"

// Class used to determine whether a creature is blinded (typically by
// the smoke from a flaming attack), and if so, for how long.
class BlindedCalculator : public StatusEffectCalculator
{
  public:
    int calculate_pct_chance_effect(CreaturePtr creature) const override;
    int calculate_duration_in_minutes(CreaturePtr creature) const override;

  protected:
    static const int BASE_BLINDED_DURATION_MEAN;
    static const int BASE_BLINDED_PCT_CHANCE;
    static const int BASE_BLINDED_CHANCE_HEALTH_MODIFIER;
};

