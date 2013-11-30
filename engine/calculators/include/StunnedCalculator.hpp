#pragma once
#include "StatusEffectCalculator.hpp"
#include "Creature.hpp"

// Class used to determine whether a creature is stunned by a bludgeoning
// attack, and if so, for how long.
class StunnedCalculator : public StatusEffectCalculator
{
  public:
    int calculate_pct_chance_effect(CreaturePtr creature) const override;
    int calculate_duration_in_minutes(CreaturePtr creature) const override;

  protected:
    static const int BASE_STUNNED_DURATION_MEAN;
    static const int BASE_STUNNED_PCT_CHANCE;
    static const int BASE_STUNNED_CHANCE_DEXTERITY_MODIFIER;
};

