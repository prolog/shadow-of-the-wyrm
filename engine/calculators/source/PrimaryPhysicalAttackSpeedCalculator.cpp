#include "NullAttackSpeedCalculator.hpp"
#include "PrimaryPhysicalAttackSpeedCalculator.hpp"
#include "Weapon.hpp"
#include "WeaponManager.hpp"

using std::dynamic_pointer_cast;

ActionCostValue PrimaryPhysicalAttackSpeedCalculator::calculate_weapon_speed(CreaturePtr creature)
{
  NullAttackSpeedCalculator nsc;
  ActionCostValue speed = nsc.calculate(creature);
  
  if (creature)
  {
    WeaponManager wm;
    WeaponPtr weapon = wm.get_weapon(creature, AttackType::ATTACK_TYPE_MELEE_PRIMARY);

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
    WeaponManager wm;
    WeaponPtr weapon = wm.get_weapon(creature, AttackType::ATTACK_TYPE_MELEE_PRIMARY);

    return (weapon != nullptr);
  }

  return false;
}

#ifdef UNIT_TESTS
#include "unit_tests/PrimaryPhysicalAttackSpeedCalculator_test.cpp"
#endif