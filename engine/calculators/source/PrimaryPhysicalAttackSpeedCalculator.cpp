#include "NullSpeedCalculator.hpp"
#include "PrimaryPhysicalAttackSpeedCalculator.hpp"

using boost::dynamic_pointer_cast;

ActionCostValue PrimaryPhysicalAttackSpeedCalculator::calculate_weapon_speed(CreaturePtr creature)
{
  NullSpeedCalculator nsc;
  ActionCostValue speed = nsc.calculate(creature);
  
  if (creature)
  {
    WeaponPtr weapon = dynamic_pointer_cast<Weapon>(creature->get_equipment().get_item(EQUIPMENT_WORN_WIELDED));

    if (weapon)
    {
      speed = weapon->get_speed();
    }
  }

  return speed;
}

bool PrimaryPhysicalAttackSpeedCalculator::has_weapon_equipped(CreaturePtr creature)
{
  if (creature)
  {
    WeaponPtr weapon = dynamic_pointer_cast<Weapon>(creature->get_equipment().get_item(EQUIPMENT_WORN_WIELDED));

    return (weapon);
  }

  return false;
}

