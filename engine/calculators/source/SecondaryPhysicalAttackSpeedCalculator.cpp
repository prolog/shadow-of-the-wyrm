#include "NullSpeedCalculator.hpp"
#include "SecondaryPhysicalAttackSpeedCalculator.hpp"
#include "Weapon.hpp"

using std::dynamic_pointer_cast;

ActionCostValue SecondaryPhysicalAttackSpeedCalculator::calculate_weapon_speed(CreaturePtr creature)
{
  NullSpeedCalculator nsc;
  ActionCostValue speed = nsc.calculate(creature);
  
  if (creature)
  {
    WeaponPtr weapon = dynamic_pointer_cast<Weapon>(creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_OFF_HAND));

    if (weapon)
    {
      speed = weapon->get_speed();
    }
  }

  return speed;
}

bool SecondaryPhysicalAttackSpeedCalculator::has_weapon_equipped(CreaturePtr creature)
{
  if (creature)
  {
    WeaponPtr weapon = dynamic_pointer_cast<Weapon>(creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_OFF_HAND));

    return (weapon != nullptr);
  }

  return false;
}

