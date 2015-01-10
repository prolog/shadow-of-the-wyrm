#include <cmath>
#include "CombatConstants.hpp"
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
// * 2, if the weapon slays the creature's race.
// - Soak
int PhysicalDamageCalculator::calculate(CreaturePtr defending_creature, const bool slays_creatures_race, const Damage& physical_damage, const int base_damage, const float soak_multiplier)
{
  int damage = 0;
  float soak_mult = soak_multiplier;

  if (defending_creature)
  {
    double resistance_multiplier = defending_creature->get_resistances().get_resistance_value(physical_damage.get_damage_type());
    double resisted_damage = base_damage * resistance_multiplier;
    
    if (resisted_damage > 0)
    {
      if (physical_damage.get_piercing())
      {
        soak_mult = 0;
      }

      // Apply soak if damage is not negative.
      // Negative damage is permitted in extreme cases - it allows things like gaining HP from
      // fire damage, etc.
      double total_soak = defending_creature->get_soak().get_current() * soak_mult;

      if (slays_creatures_race)
      {
        resisted_damage *= CombatConstants::RACE_SLAY_MULTIPLIER;
      }
      
      damage = static_cast<int>(ceil(std::max<double>(0, resisted_damage - total_soak)));
    }
    else
    {
      // If the damage is negative (healing), ignore soak.
      damage = static_cast<int>(resisted_damage);
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

// Physical damage gets +1 for every 5 points of Strength over 10, plus
// the creature's base additional damage.
Damage PhysicalDamageCalculator::calculate_base_damage_with_bonuses_or_penalties(CreaturePtr attacking_creature)
{
  Damage base_damage = calculate_base_damage_object(attacking_creature);
  
  if (attacking_creature)
  {
    int current_modifier = base_damage.get_modifier() + attacking_creature->get_addl_damage().get_current();
    int bac_modifier = static_cast<int>(attacking_creature->get_blood().get_blood_alcohol_content() * 100) / 2;

    current_modifier += get_statistic_based_damage_modifier(attacking_creature);
    current_modifier += bac_modifier;
    
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

#ifdef UNIT_TESTS
#include "unit_tests/PhysicalDamageCalculator_test.cpp"
#endif

