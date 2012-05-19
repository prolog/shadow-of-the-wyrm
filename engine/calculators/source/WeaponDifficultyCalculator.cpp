#include "CombatConstants.hpp"
#include "WeaponDifficultyCalculator.hpp"

using boost::dynamic_pointer_cast;

int WeaponDifficultyCalculator::calculate(CreaturePtr creature, AttackType attack_type)
{
  int difficulty = 0;
  WeaponPtr weapon;

  if (creature)
  {
    switch(attack_type)
    {
      case ATTACK_TYPE_RANGED:
      case ATTACK_TYPE_MELEE_PRIMARY:
        weapon = dynamic_pointer_cast<Weapon>(creature->get_equipment().get_item(EQUIPMENT_WORN_RIGHT_HAND));
        difficulty = get_difficulty_for_weapon(weapon);
        break;
      case ATTACK_TYPE_MELEE_SECONDARY:
        weapon = dynamic_pointer_cast<Weapon>(creature->get_equipment().get_item(EQUIPMENT_WORN_LEFT_HAND));
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
