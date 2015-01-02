#include "RangedPhysicalDamageCalculator.hpp"

RangedPhysicalDamageCalculator::RangedPhysicalDamageCalculator()
: PhysicalDamageCalculator(AttackType::ATTACK_TYPE_RANGED)
{
}

int RangedPhysicalDamageCalculator::get_statistic_based_damage_modifier(CreaturePtr attacking_creature)
{
  int modifier = 0;
  
  if (attacking_creature)
  {
    int current_dex = attacking_creature->get_dexterity().get_current();
    
    if (current_dex > DAMAGE_STAT_BASELINE)
    {
      current_dex -= DAMAGE_STAT_BASELINE;
      modifier = current_dex / DAMAGE_STAT_DIVISOR;
    }
  }
  
  return modifier;
}
