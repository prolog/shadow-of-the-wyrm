#include <cmath>
#include "PhysicalDamageCalculator.hpp"
#include "WeaponManager.hpp"

// Always check to see if a stat is > 10 before considering it for a damage bonus.
const int PhysicalDamageCalculator::DAMAGE_STAT_BASELINE = 10;

// A creature gets +1 damage for every 5 points over 10 in the appropriate statistic (strength for physical,
// dex for ranged, etc).
const int PhysicalDamageCalculator::DAMAGE_STAT_DIVISOR = 5;

PhysicalDamageCalculator::PhysicalDamageCalculator(const AttackType new_attack_type)
: DamageCalculator(new_attack_type)
{
}

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

// Get the base damage.
Damage PhysicalDamageCalculator::calculate_base_damage_object(CreaturePtr attacking_creature)
{
  WeaponManager wm;
  return wm.get_damage(attacking_creature, attack_type);
}

// Physical damage gets +1 for every 5 points of Strength over 10.
Damage PhysicalDamageCalculator::calculate_base_damage_with_bonuses_or_penalties(CreaturePtr attacking_creature)
{
  Damage base_damage = calculate_base_damage_object(attacking_creature);
  
  if (attacking_creature)
  {
    int current_modifier = get_statistic_based_damage_modifier(attacking_creature);
    base_damage.set_modifier(current_modifier);
  }
  
  return base_damage;
}

// For physical damage (not ranged), Str is the stat used to calculate the damage bonus.
// +1 damage for every 5 points of str > 10.
int PhysicalDamageCalculator::get_statistic_based_damage_modifier(CreaturePtr attacking_creature)
{
  int modifier = 0;
  
  if (attacking_creature)
  {
    int current_strength = attacking_creature->get_strength().get_current();

    if (current_strength > DAMAGE_STAT_BASELINE)
    {
      current_strength -= DAMAGE_STAT_BASELINE;
      modifier = current_strength / DAMAGE_STAT_DIVISOR;
    }    
  }
  
  return modifier;
}
