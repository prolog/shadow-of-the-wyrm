#include "StatusEffectCalculator.hpp"

// The chance of the effect is the chance of the effect for the
// implementing class, plus the effect bonus.
int StatusEffectCalculator::chance_of_effect(CreaturePtr creature, const int effect_bonus) const
{
  return calculate_pct_chance_effect(creature) + effect_bonus;
}

