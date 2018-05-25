#include "NullAttackSpeedCalculator.hpp"
#include "RangedAttackSpeedCalculator.hpp"
#include "Weapon.hpp"

using std::dynamic_pointer_cast;

ActionCostValue RangedAttackSpeedCalculator::calculate(CreaturePtr creature)
{
  NullAttackSpeedCalculator nsc;
  ActionCostValue action_cost_value = nsc.calculate(creature);

  if (creature)
  {
    Equipment& eq = creature->get_equipment();
    WeaponPtr weapon = dynamic_pointer_cast<Weapon>(eq.get_item(EquipmentWornLocation::EQUIPMENT_WORN_RANGED_WEAPON));

    // If a ranged weapon is equipped, the attack speed is that of the ranged weapon.
    // Otherwise, the attack speed is that of the ammunition.
    // Either one of the above should always be true.  However, if it is not, then the
    // null speed calculator's value is used.
    if (weapon)
    {
      action_cost_value = calculate_speed_for_weapon(creature, weapon, true);
    }
    else
    {
      WeaponPtr ammunition = dynamic_pointer_cast<Weapon>(eq.get_item(EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION));

      if (ammunition)
      {
        action_cost_value = calculate_speed_for_weapon(creature, ammunition, true);
      }
    }
  }

  return action_cost_value;
}

#ifdef UNIT_TESTS
#include "unit_tests/RangedAttackSpeedCalculator_test.cpp"
#endif
