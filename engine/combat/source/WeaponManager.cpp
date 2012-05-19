#include "CombatConstants.hpp"
#include "WeaponManager.hpp"

using boost::dynamic_pointer_cast;

// Get the weapon for the given attack type.  The returned pointer
// WILL BE NULL if there is nothing equipped in the appropriate slot.
WeaponPtr WeaponManager::get_weapon(CreaturePtr creature, const AttackType attack_type)
{
  WeaponPtr weapon;
  
  if (creature)
  {
    switch(attack_type)
    {
      case ATTACK_TYPE_RANGED:
      case ATTACK_TYPE_MELEE_PRIMARY:
        weapon = dynamic_pointer_cast<Weapon>(creature->get_equipment().get_item(EQUIPMENT_WORN_RIGHT_HAND));
        break;
      case ATTACK_TYPE_MELEE_SECONDARY:
        weapon = dynamic_pointer_cast<Weapon>(creature->get_equipment().get_item(EQUIPMENT_WORN_LEFT_HAND));
        break;
      case ATTACK_TYPE_MAGICAL:
      default:
        break;
    }
  }
  
  return weapon;
}

// Get the damage for the given attack type
Damage WeaponManager::get_damage(CreaturePtr creature, const AttackType attack_type)
{
  WeaponPtr weapon = get_weapon(creature, attack_type);
  
  if (weapon)
  {
    return weapon->get_damage();
  }
  else
  {
    return creature->get_base_damage();
  }
}
 
// Get the damage type for the given attack type.
DamageType WeaponManager::get_damage_type(CreaturePtr creature, const AttackType attack_type)
{
  Damage damage = get_damage(creature, attack_type);
  return damage.get_damage_type();
}
