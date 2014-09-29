#include "NullSpeedCalculator.hpp"
#include "TertiaryUnarmedPhysicalAttackSpeedCalculator.hpp"

ActionCostValue TertiaryUnarmedPhysicalAttackSpeedCalculator::calculate_weapon_speed(CreaturePtr creature)
{
  NullSpeedCalculator nsc;

  return nsc.calculate(creature);
}

bool TertiaryUnarmedPhysicalAttackSpeedCalculator::has_weapon_equipped(CreaturePtr creature)
{
  return false;
}
