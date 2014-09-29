#include "CombatConstants.hpp"
#include "ToHitCalculatorFactory.hpp"
#include "LightMeleeAndRangedWeaponToHitCalculator.hpp"
#include "HeavyWeaponToHitCalculator.hpp"
#include "MagicToHitCalculator.hpp"
#include "WeaponManager.hpp"

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
    case ATTACK_TYPE_MELEE_SECONDARY:
    case ATTACK_TYPE_MELEE_TERTIARY_UNARMED:
    {
      creature_weapon = weapon_manager.get_weapon(creature, attack_type);
      calculator = create_to_hit_calculator_given_weapon(size, creature_weapon, attack_type);
      break;
    }
    case ATTACK_TYPE_RANGED:
      calculator = std::make_shared<LightMeleeAndRangedWeaponToHitCalculator>(attack_type);
      break;
    case ATTACK_TYPE_MAGICAL: // fall through intentionally
    default:
      calculator = std::make_shared<MagicToHitCalculator>();
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
// So if a fae punches you, it's a light attack.
//
// If a goblin kicks you, it's a light attack.
//
// And if a dragon claws you, it's a heavy attack.
ToHitCalculatorPtr ToHitCalculatorFactory::create_to_hit_calculator_given_weapon(const CreatureSize creature_size, WeaponPtr weapon, const AttackType attack_type)
{
  ToHitCalculatorPtr calculator;
  
  if (weapon)
  {
    double weight = weapon->get_weight().get_weight_in_lbs();
    
    // JCD FIXME magic number
    if (weight > CombatConstants::HEAVY_WEAPON_THRESHOLD_IN_LBS)
    {
      calculator = std::make_shared<HeavyWeaponToHitCalculator>(attack_type);
    }
    else
    {
      calculator = std::make_shared<LightMeleeAndRangedWeaponToHitCalculator>(attack_type);
    }
  }
  else
  {
    if (creature_size >= CREATURE_SIZE_HUGE)
    {
      calculator = std::make_shared<HeavyWeaponToHitCalculator>();
    }
    else
    {
      calculator = std::make_shared<LightMeleeAndRangedWeaponToHitCalculator>(attack_type);
    }
  }
  
  return calculator;
}
