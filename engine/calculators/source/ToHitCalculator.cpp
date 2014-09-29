#include "SkillManager.hpp"
#include "StatusEffectFactory.hpp"
#include "ToHitCalculator.hpp"
#include "WeaponManager.hpp"

using namespace std;

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

  // Apply the weapon modifier.
  SkillType st = SKILL_MELEE_UNARMED;
  
  if (attack_type == ATTACK_TYPE_RANGED)
  {
    st = weapon->get_trained_ranged_skill();
  }
  else
  {
    if (weapon)
    {
      st = weapon->get_trained_skill();
    }
  }

  weapon_bonus += (sm.get_skill_value(creature, st) / 2);  
  return weapon_bonus;
}

int ToHitCalculator::get_status_bonus(CreaturePtr creature)
{
  int status_bonus = 0;

  // Apply any status modifiers.
  CreatureStatusMap statuses = creature->get_statuses();
  for(const CreatureStatusMap::value_type& status_pair : statuses)
  {
    string status_id = status_pair.first;
    bool status_applied = status_pair.second;

    if (status_applied)
    {
      StatusEffectPtr status = StatusEffectFactory::create_status_effect(status_id);
      status_bonus += status->get_to_hit_bonus(creature);
    }
  }

  return status_bonus;
}
