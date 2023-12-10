#include "SecondaryPhysicalAttackSpeedCalculator.hpp"
#include "Weapon.hpp"
#include "WeaponManager.hpp"

using std::dynamic_pointer_cast;

const int SecondaryPhysicalAttackSpeedCalculator::BASE_SPEED_PENALTY = 20;

ActionCostValue SecondaryPhysicalAttackSpeedCalculator::calculate_weapon_speed(CreaturePtr creature)
{
  ActionCostValue speed = calculate_speed_penalty(creature);
  
  if (creature)
  {
    WeaponManager wm;
    WeaponPtr weapon = wm.get_weapon(creature, AttackType::ATTACK_TYPE_MELEE_SECONDARY);

    if (weapon)
    {
      speed += calculate_speed_for_weapon(creature, weapon);
    }
  }

  return speed;
}

bool SecondaryPhysicalAttackSpeedCalculator::has_weapon_equipped(CreaturePtr creature)
{
  if (creature)
  {
    WeaponManager wm;
    WeaponPtr weapon = wm.get_weapon(creature, AttackType::ATTACK_TYPE_MELEE_SECONDARY);

    return (weapon != nullptr);
  }

  return false;
}

int SecondaryPhysicalAttackSpeedCalculator::calculate_speed_penalty(CreaturePtr creature)
{
  int speed_penalty = BASE_SPEED_PENALTY;

  if (creature != nullptr)
  {
    int dual_wield_skill = creature->get_skills().get_value(SkillType::SKILL_GENERAL_DUAL_WIELD);

    // For every 5 points of dual wield, reduce the speed penalty by 1.
    speed_penalty -= (dual_wield_skill / 5);
  }

  return std::max(1, speed_penalty);
}
