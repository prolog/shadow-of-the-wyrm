#include "AttackSpeedCalculator.hpp"

ActionCostValue AttackSpeedCalculator::calculate_speed_for_weapon(CreaturePtr creature, WeaponPtr weapon, const bool ranged)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;

  if (creature != nullptr && weapon != nullptr)
  {
    acv = weapon->get_speed();
    SkillType weapon_skill = weapon->get_trained_skill();

    if (ranged)
    {
      weapon_skill = weapon->get_trained_ranged_skill();
    }

    if (weapon_skill == SkillType::SKILL_MELEE_EXOTIC || weapon_skill == SkillType::SKILL_RANGED_EXOTIC)
    {
      acv *= calculate_exotic_attack_speed_multiplier(creature, weapon_skill);
    }
  }
  else
  {
    acv = ActionCostConstants::DEFAULT;
  }

  return acv;
}

int AttackSpeedCalculator::calculate_exotic_attack_speed_multiplier(CreaturePtr creature, const SkillType weapon_skill)
{
  int multiplier = 1;

  if (creature != nullptr)
  {
    multiplier = 5 - (creature->get_skills().get_value(weapon_skill) / 25);
  }

  return std::max(1, multiplier);
}

