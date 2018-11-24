#include "gtest/gtest.h"

std::pair<CreaturePtr, WeaponPtr> setup_creature(const int weapon_speed, const SkillType skill_type)
{
  CreaturePtr creature = std::make_shared<Creature>();
  WeaponPtr weapon = std::make_shared<MeleeWeapon>();

  creature->get_equipment().set_item(weapon, EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);

  weapon->set_speed(weapon_speed);
  weapon->set_trained_skill(skill_type);

  return make_pair(creature, weapon);
}

TEST(SW_Engine_Calculators_PrimaryPhysicalAttackSpeedCalculator, weapon_speed)
{
  auto cr_pair = setup_creature(11, SkillType::SKILL_MELEE_AXES);
  CreaturePtr creature = cr_pair.first;

  PrimaryPhysicalAttackSpeedCalculator calc;
  EXPECT_EQ(11, calc.calculate(creature));
}

TEST(SW_Engine_Calculators_PrimaryPhysicalAttackSpeedCalculator, exotics_weapon_speed)
{
  auto cr_pair = setup_creature(10, SkillType::SKILL_MELEE_EXOTIC);
  CreaturePtr creature = cr_pair.first;

  PrimaryPhysicalAttackSpeedCalculator calc;
  EXPECT_EQ(50, calc.calculate(creature));

  creature->get_skills().set_value(SkillType::SKILL_MELEE_EXOTIC, 27);
  EXPECT_EQ(40, calc.calculate(creature));

  creature->get_skills().set_value(SkillType::SKILL_MELEE_EXOTIC, 50);
  EXPECT_EQ(30, calc.calculate(creature));

  creature->get_skills().set_value(SkillType::SKILL_MELEE_EXOTIC, 88);
  EXPECT_EQ(20, calc.calculate(creature));

  creature->get_skills().set_value(SkillType::SKILL_MELEE_EXOTIC, 100);
  EXPECT_EQ(10, calc.calculate(creature));
}