#pragma once
#include "StatusEffectCalculator.hpp"
#include "Creature.hpp"

// Class used to determine whether a creature is spellbound (can move,
// but cannot act) as the result of an arcane attack, and for how long.
class SpellboundCalculator : public StatusEffectCalculator
{
  public:
    int calculate_pct_chance_effect(CreaturePtr creature) const override;
    int calculate_duration_in_minutes(CreaturePtr creature) const override;

  protected:
    static const int BASE_SPELLBOUND_DURATION_MEAN;
    static const int BASE_SPELLBOUND_PCT_CHANCE;
    static const int BASE_SPELLBOUND_CHANCE_WILLPOWER_MODIFIER;
};

