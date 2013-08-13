#include "CombatConstants.hpp"
#include "ToHitCalculatorFactory.hpp"
#include "WeaponDifficultyCalculator.hpp"

using boost::dynamic_pointer_cast;

int WeaponDifficultyCalculator::calculate_base_difficulty(CreaturePtr creature, const AttackType attack_type)
{
  int difficulty = 0;
  WeaponPtr weapon;

  if (creature)
  {
    switch(attack_type)
    {
      case ATTACK_TYPE_RANGED:
      case ATTACK_TYPE_MELEE_PRIMARY:
        weapon = dynamic_pointer_cast<Weapon>(creature->get_equipment().get_item(EQUIPMENT_WORN_WIELDED));
        difficulty = get_difficulty_for_weapon(weapon);
        break;
      case ATTACK_TYPE_MELEE_SECONDARY:
        weapon = dynamic_pointer_cast<Weapon>(creature->get_equipment().get_item(EQUIPMENT_WORN_OFF_HAND));
        difficulty = get_difficulty_for_weapon(weapon);
        break;
      case ATTACK_TYPE_MAGICAL:
      default:
        difficulty = get_difficulty_for_weapon(weapon);
        break;
    }
  }

  return difficulty;
}

int WeaponDifficultyCalculator::get_difficulty_for_weapon(WeaponPtr weapon)
{
  int difficulty;

  if (weapon)
  {
    difficulty = weapon->get_difficulty();
  }
  else
  {
    difficulty = CombatConstants::BASE_WEAPON_DIFFICULTY;
  }
  
  return difficulty;
}

// Get the "total" difficulty for the weapon.  This is not directly used in
// game, but is useful for players because they can see the character's
// to-hit reflected by the lower difficulty.
int WeaponDifficultyCalculator::calculate_total_difficulty_for_display(CreaturePtr creature, const AttackType attack_type)
{
  ToHitCalculatorPtr th_calculator = ToHitCalculatorFactory::create_to_hit_calculator(creature, attack_type);

  int base_difficulty = calculate_base_difficulty(creature, attack_type);
  // JCD FIXME: Move this into a function on the WeaponDifficultyCalculator.
  // Since "total difficulty" as a concept is only used here, it should go into 
  // WDC.  The CombatManager uses base_roll + to_hit, instead of "weapon_difficulty - to_hit".
  int total_difficulty = base_difficulty - th_calculator->calculate(creature);

  return total_difficulty;
}