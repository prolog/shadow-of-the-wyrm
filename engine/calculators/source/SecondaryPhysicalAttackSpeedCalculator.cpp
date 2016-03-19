#include "SecondaryPhysicalAttackSpeedCalculator.hpp"
#include "Weapon.hpp"

using std::dynamic_pointer_cast;

const int SecondaryPhysicalAttackSpeedCalculator::BASE_SPEED_PENALTY = 20;

ActionCostValue SecondaryPhysicalAttackSpeedCalculator::calculate_weapon_speed(CreaturePtr creature)
{
  ActionCostValue speed = calculate_speed_penalty(creature);
  
  if (creature)
  {
    WeaponPtr weapon = dynamic_pointer_cast<Weapon>(creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_OFF_HAND));

    if (weapon)
    {
      speed += weapon->get_speed();
    }
  }

  return speed;
}

bool SecondaryPhysicalAttackSpeedCalculator::has_weapon_equipped(CreaturePtr creature)
{
  if (creature)
  {
    WeaponPtr weapon = dynamic_pointer_cast<Weapon>(creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_OFF_HAND));

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
