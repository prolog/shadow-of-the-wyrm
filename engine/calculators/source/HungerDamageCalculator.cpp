#include "HungerDamageCalculator.hpp"

const int HungerDamageCalculator::HUNGER_DAMAGE_PER_TICK = 10;

int HungerDamageCalculator::calculate_hunger_damage(CreaturePtr creature, const int num_ticks) const
{
  return (num_ticks * HUNGER_DAMAGE_PER_TICK);
}
