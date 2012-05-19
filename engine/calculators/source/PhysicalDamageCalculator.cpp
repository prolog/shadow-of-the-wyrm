#include <cmath>
#include "PhysicalDamageCalculator.hpp"

// Physical Damage =
// (Rolled damage * Resistance to that damage type)
// - Soak
int PhysicalDamageCalculator::calculate(CreaturePtr defending_creature, const Damage& physical_damage, const int base_damage, const float soak_multiplier)
{
  int damage = 0;

  if (defending_creature)
  {
    double resistance_multiplier = defending_creature->get_resistances().get_resistance_value(physical_damage.get_damage_type());
    double resisted_damage = base_damage * resistance_multiplier;
    
    if (resisted_damage > 0)
    {
      // Apply soak if damage is not negative.
      // Negative damage is permitted in extreme cases - it allows things like gaining HP from
      // fire damage, etc.
      double total_soak = defending_creature->get_soak().get_current() * soak_multiplier;
      
      damage = ceil(fmax(0, resisted_damage - total_soak));
    }
    else
    {
      // If the damage is negative (healing), ignore soak.
      damage = ceil(damage);
    }
  }

  return damage;
}
