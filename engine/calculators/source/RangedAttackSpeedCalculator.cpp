#include "NullSpeedCalculator.hpp"
#include "RangedAttackSpeedCalculator.hpp"

using boost::dynamic_pointer_cast;

ActionCostValue RangedAttackSpeedCalculator::calculate(CreaturePtr creature)
{
  NullSpeedCalculator nsc;
  ActionCostValue action_cost_value = nsc.calculate(creature);

  if (creature)
  {
    Equipment& eq = creature->get_equipment();
    WeaponPtr weapon = dynamic_pointer_cast<Weapon>(eq.get_item(EQUIPMENT_WORN_RANGED_WEAPON));

    // If a ranged weapon is equipped, the attack speed is that of the ranged weapon.
    // Otherwise, the attack speed is that of the ammunition.
    // Either one of the above should always be true.  However, if it is not, then the
    // null speed calculator's value is used.
    if (weapon)
    {
      action_cost_value = weapon->get_speed();
    }
    else
    {
      WeaponPtr ammunition = dynamic_pointer_cast<Weapon>(eq.get_item(EQUIPMENT_WORN_AMMUNITION));

      if (ammunition)
      {
        action_cost_value = ammunition->get_speed();
      }
    }
  }

  return action_cost_value;
}

