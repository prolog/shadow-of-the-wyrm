#pragma once
#include "StatusEffectCalculator.hpp"
#include "Creature.hpp"

// Class used for all status effects that are based on e.g. in-game turns,
// rather than in-game time.  The engine will take a max-int value to mean
// that the status should be added to the creature, but no timer information
// added.
class UntimedStatusCalculator : public StatusEffectCalculator
{
  public:
    int calculate_duration_in_minutes(CreaturePtr creature) const override;

  protected:
    int calculate_pct_chance_effect(CreaturePtr creature) const override;
};

