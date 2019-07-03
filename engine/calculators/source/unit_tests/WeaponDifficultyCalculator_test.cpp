#include "gtest/gtest.h"
#include "Ammunition.hpp"

TEST(SW_Engine_Calculators_WeaponDifficultyCalculator, calculate_base_difficulty)
{
  CreaturePtr creature = std::make_shared<Creature>();

  WeaponPtr sword = std::make_shared<MeleeWeapon>();
  WeaponPtr thrown_rock = std::make_shared<Ammunition>();
  WeaponPtr bow = std::make_shared<RangedWeapon>();

  const int SWORD_DIFFICULTY = 40;
  const int BOW_DIFFICULTY = 46;
  const int THROWN_ROCK_DIFFICULTY = 50;

  sword->set_difficulty(SWORD_DIFFICULTY);
  bow->set_difficulty(BOW_DIFFICULTY);
  thrown_rock->set_difficulty(THROWN_ROCK_DIFFICULTY);

  WeaponDifficultyCalculator wdc;

  creature->get_equipment().set_item(sword, EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);
  creature->get_equipment().set_item(thrown_rock, EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION);

  EXPECT_EQ(SWORD_DIFFICULTY, wdc.calculate_base_difficulty(creature, AttackType::ATTACK_TYPE_MELEE_PRIMARY));
  EXPECT_EQ(THROWN_ROCK_DIFFICULTY, wdc.calculate_base_difficulty(creature, AttackType::ATTACK_TYPE_RANGED));

  creature->get_equipment().remove_item(EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION);
  creature->get_equipment().set_item(bow, EquipmentWornLocation::EQUIPMENT_WORN_RANGED_WEAPON);

  EXPECT_EQ(BOW_DIFFICULTY, wdc.calculate_base_difficulty(creature, AttackType::ATTACK_TYPE_RANGED));

  creature->get_equipment().remove_item(EquipmentWornLocation::EQUIPMENT_WORN_RANGED_WEAPON);

  EXPECT_EQ(CombatConstants::BASE_WEAPON_DIFFICULTY, wdc.calculate_base_difficulty(creature, AttackType::ATTACK_TYPE_RANGED));
}

TEST(SW_Engine_Calculators_WeaponDifficultyCalculator, get_weapon_difficulty)
{
  WeaponPtr sword = std::make_shared<MeleeWeapon>();
  sword->set_difficulty(45);

  WeaponPtr thrown_rock = std::make_shared<Ammunition>();
  thrown_rock->set_difficulty(50);

  WeaponPtr bow = std::make_shared<RangedWeapon>();
  bow->set_difficulty(40);

  std::vector<WeaponPtr> weapons = {bow, sword, thrown_rock};
  WeaponDifficultyCalculator wdc;

  for (WeaponPtr weapon : weapons)
  {
    EXPECT_EQ(weapon->get_difficulty(), wdc.get_difficulty_for_weapon(weapon));
  }

  EXPECT_EQ(CombatConstants::BASE_WEAPON_DIFFICULTY, wdc.get_difficulty_for_weapon(nullptr));
}
