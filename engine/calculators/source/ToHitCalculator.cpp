#include "SkillManager.hpp"
#include "ToHitCalculator.hpp"
#include "WeaponManager.hpp"

const int ToHitCalculator::NWP_SKILL_BONUS_DIVISOR = 5;

ToHitCalculator::ToHitCalculator()
: attack_type(ATTACK_TYPE_MELEE_PRIMARY)
{
}

ToHitCalculator::ToHitCalculator(const AttackType new_attack_type)
: attack_type(new_attack_type)
{
}

int ToHitCalculator::get_weapon_bonus(CreaturePtr creature)
{
  int weapon_bonus = 0;
  
  WeaponManager wm;
  WeaponPtr weapon = wm.get_weapon(creature, attack_type);
  
  SkillManager sm;

  if (weapon)
  {
    SkillType st = weapon->get_trained_skill();

    if (attack_type == ATTACK_TYPE_RANGED)
    {
      st = weapon->get_trained_ranged_skill();
    }

    weapon_bonus += (sm.get_skill_value(creature, st) / 2);
  }
  
  return weapon_bonus;
}
