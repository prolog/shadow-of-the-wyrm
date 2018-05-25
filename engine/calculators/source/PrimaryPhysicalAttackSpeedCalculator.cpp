#include "NullAttackSpeedCalculator.hpp"
#include "PrimaryPhysicalAttackSpeedCalculator.hpp"
#include "Weapon.hpp"

using std::dynamic_pointer_cast;

ActionCostValue PrimaryPhysicalAttackSpeedCalculator::calculate_weapon_speed(CreaturePtr creature)
{
  NullAttackSpeedCalculator nsc;
  ActionCostValue speed = nsc.calculate(creature);
  
  if (creature)
  {
    WeaponPtr weapon = dynamic_pointer_cast<Weapon>(creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_WIELDED));

    if (weapon)
    {
      speed = calculate_speed_for_weapon(creature, weapon);
    }
  }

  return speed;
}

bool PrimaryPhysicalAttackSpeedCalculator::has_weapon_equipped(CreaturePtr creature)
{
  if (creature)
  {
    WeaponPtr weapon = dynamic_pointer_cast<Weapon>(creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_WIELDED));

    return (weapon != nullptr);
  }

  return false;
}

#ifdef UNIT_TESTS
#include "unit_tests/PrimaryPhysicalAttackSpeedCalculator_test.cpp"
#endif