#include "gtest/gtest.h"
#include "Ammunition.hpp"

std::pair<CreaturePtr, WeaponPtr> setup_launcher_creature(const int weapon_speed, const SkillType skill_type)
{
  CreaturePtr creature = std::make_shared<Creature>();
  WeaponPtr weapon = std::make_shared<RangedWeapon>();

  creature->get_equipment().set_item(weapon, EquipmentWornLocation::EQUIPMENT_WORN_RANGED_WEAPON);

  weapon->set_speed(weapon_speed);
  weapon->set_trained_ranged_skill(skill_type);

  return make_pair(creature, weapon);
}

std::pair<CreaturePtr, WeaponPtr> setup_thrown_creature(const int weapon_speed, const SkillType skill_type)
{
  CreaturePtr creature = std::make_shared<Creature>();
  WeaponPtr weapon = std::make_shared<Ammunition>();

  creature->get_equipment().set_item(weapon, EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION);

  weapon->set_speed(weapon_speed);
  weapon->set_trained_ranged_skill(skill_type);

  return make_pair(creature, weapon);
}

TEST(SW_Engine_Calculators_RangedAttackSpeedCalculator, weapon_speed)
{
  auto cr_pair = setup_launcher_creature(11, SkillType::SKILL_RANGED_BOWS);
  CreaturePtr launcher_creature = cr_pair.first;

  cr_pair = setup_thrown_creature(14, SkillType::SKILL_RANGED_ROCKS);
  CreaturePtr thrown_creature = cr_pair.first;

  RangedAttackSpeedCalculator calc;
  EXPECT_EQ(11, calc.calculate(launcher_creature));
  EXPECT_EQ(14, calc.calculate(thrown_creature));
}

TEST(SW_Engine_Calculators_RangedAttackSpeedCalculator, exotics_weapon_speed)
{
  auto cr_pair = setup_launcher_creature(11, SkillType::SKILL_RANGED_EXOTIC);
  CreaturePtr launcher_creature = cr_pair.first;

  cr_pair = setup_thrown_creature(14, SkillType::SKILL_RANGED_EXOTIC);
  CreaturePtr thrown_creature = cr_pair.first;

  RangedAttackSpeedCalculator calc;
  EXPECT_EQ(55, calc.calculate(launcher_creature));
  EXPECT_EQ(70, calc.calculate(thrown_creature));

  launcher_creature->get_skills().set_value(SkillType::SKILL_RANGED_EXOTIC, 27);
  thrown_creature->get_skills().set_value(SkillType::SKILL_RANGED_EXOTIC, 27);
  EXPECT_EQ(44, calc.calculate(launcher_creature));
  EXPECT_EQ(56, calc.calculate(thrown_creature));

  launcher_creature->get_skills().set_value(SkillType::SKILL_RANGED_EXOTIC, 53);
  thrown_creature->get_skills().set_value(SkillType::SKILL_RANGED_EXOTIC, 53);
  EXPECT_EQ(33, calc.calculate(launcher_creature));
  EXPECT_EQ(42, calc.calculate(thrown_creature));

  launcher_creature->get_skills().set_value(SkillType::SKILL_RANGED_EXOTIC, 75);
  thrown_creature->get_skills().set_value(SkillType::SKILL_RANGED_EXOTIC, 75);
  EXPECT_EQ(22, calc.calculate(launcher_creature));
  EXPECT_EQ(28, calc.calculate(thrown_creature));

  launcher_creature->get_skills().set_value(SkillType::SKILL_RANGED_EXOTIC, 100);
  thrown_creature->get_skills().set_value(SkillType::SKILL_RANGED_EXOTIC, 100);
  EXPECT_EQ(11, calc.calculate(launcher_creature));
  EXPECT_EQ(14, calc.calculate(thrown_creature));
}