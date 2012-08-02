#include "MagicalDamageCalculator.hpp"

MagicalDamageCalculator::MagicalDamageCalculator()
: DamageCalculator(ATTACK_TYPE_MAGICAL)
{
}

// Magical damage =
// Rolled damage * Resistance to that damage
//
// (Soak is not considered for magical damage - resistances become far more powerful.)
int MagicalDamageCalculator::calculate(CreaturePtr defending_creature, const Damage& magical_damage, const int base_damage, const float soak_multiplier)
{
  int damage = base_damage;

  if (defending_creature)
  {
    double resistance_multiplier = defending_creature->get_resistances().get_resistance_value(magical_damage.get_damage_type());
    
    damage = base_damage * resistance_multiplier;
  }
  
  return damage;
}

Damage MagicalDamageCalculator::calculate_base_damage_object(CreaturePtr creature)
{
  // JCD FIXME
  Damage d;
  return d;
}

Damage MagicalDamageCalculator::calculate_base_damage_with_bonuses_or_penalties(CreaturePtr creature)
{
  // JCD FIXME
  return calculate_base_damage_object(creature);
}
