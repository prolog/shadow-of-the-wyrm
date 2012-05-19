#include <boost/make_shared.hpp>
#include "CombatConstants.hpp"
#include "ToHitCalculatorFactory.hpp"
#include "LightMeleeAndRangedWeaponToHitCalculator.hpp"
#include "HeavyWeaponToHitCalculator.hpp"
#include "MagicToHitCalculator.hpp"
#include "WeaponManager.hpp"

using boost::make_shared;

ToHitCalculatorFactory::ToHitCalculatorFactory()
{
}

ToHitCalculatorFactory::~ToHitCalculatorFactory()
{
}

// Create the appropriate to-hit calculator and return it
ToHitCalculatorPtr ToHitCalculatorFactory::create_to_hit_calculator(CreaturePtr creature, AttackType attack_type)
{
  ToHitCalculatorPtr calculator;
  WeaponManager weapon_manager;
    
  WeaponPtr creature_weapon;
  CreatureSize size = creature->get_size();
  
  switch(attack_type)
  {
    case ATTACK_TYPE_MELEE_PRIMARY:
    {
      creature_weapon = weapon_manager.get_weapon(creature, attack_type);
      calculator = create_to_hit_calculator_given_weapon(size, creature_weapon);
      break;
    }
    case ATTACK_TYPE_MELEE_SECONDARY:
    {
      creature_weapon = weapon_manager.get_weapon(creature, attack_type);
      calculator = create_to_hit_calculator_given_weapon(size, creature_weapon);
      break;
    }
    case ATTACK_TYPE_RANGED:
      calculator = make_shared<LightMeleeAndRangedWeaponToHitCalculator>();
      break;
    case ATTACK_TYPE_MAGICAL: // Fall through intentionally
    default:
      calculator = make_shared<MagicToHitCalculator>();
      break;
  }
  
  return calculator;
}

// Return a to-hit calculator given a weapon.
// If the weapon is more than 30 lbs, it is heavy.
// Otherwise (and if it's null and we should be using the creature's base attack),
// it is always light.
//
// The lone exception is if the creature is Huge or bigger.
//
// So if a pixie punches you, it's a light attack.
//
// If a goblin kicks you, it's a light attack.
//
// And if a dragon claws you, it's a heavy attack.
ToHitCalculatorPtr ToHitCalculatorFactory::create_to_hit_calculator_given_weapon(const CreatureSize creature_size, WeaponPtr weapon)
{
  ToHitCalculatorPtr calculator;
  
  if (weapon)
  {
    double weight = weapon->get_weight().get_weight_in_lbs();
    
    // JCD FIXME magic number
    if (weight > CombatConstants::HEAVY_WEAPON_THRESHOLD_IN_LBS)
    {
      calculator = make_shared<HeavyWeaponToHitCalculator>();
    }
    else
    {
      calculator = make_shared<LightMeleeAndRangedWeaponToHitCalculator>();
    }
  }
  else
  {
    if (creature_size >= CREATURE_SIZE_HUGE)
    {
      calculator = make_shared<HeavyWeaponToHitCalculator>();
    }
    else
    {
      calculator = make_shared<LightMeleeAndRangedWeaponToHitCalculator>();
    }
  }
  
  return calculator;
}
