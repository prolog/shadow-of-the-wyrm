#include "gtest/gtest.h"
#include "Weapon.hpp"

TEST(SW_Engine_Calculator_UnarmedCombatCalculator, is_unarmed)
{
  UnarmedCombatCalculator ucc;
  CreaturePtr creature = std::make_shared<Creature>();

  std::vector<AttackType> not_unarmed = { AttackType::ATTACK_TYPE_MAGICAL, AttackType::ATTACK_TYPE_RANGED, AttackType::ATTACK_TYPE_UNDEFINED };

  std::vector<AttackType> unarmed = { AttackType::ATTACK_TYPE_MELEE_PRIMARY, AttackType::ATTACK_TYPE_MELEE_SECONDARY, AttackType::ATTACK_TYPE_MELEE_TERTIARY_UNARMED };

  // When unarmed, each of the attack types in "unarmed" should be true.
  for (const AttackType atype : unarmed)
  {
    EXPECT_TRUE(ucc.is_attack_unarmed(creature, atype));
  }

  // When armed, primary/secondary should be true only if the weapon's
  // trained skill is unarmed.
  std::vector<std::pair<SkillType, bool>> skill_and_exp = { {SkillType::SKILL_MELEE_BLUDGEONS, false}, {SkillType::SKILL_MELEE_LONG_BLADES, false}, {SkillType::SKILL_MELEE_UNARMED, true} };

  for (const auto& se : skill_and_exp)
  {
    MeleeWeaponPtr mw = std::make_shared<MeleeWeapon>();
    mw->set_trained_skill(se.first);
    creature->get_equipment().set_item(mw, EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);

    EXPECT_EQ(se.second, ucc.is_attack_unarmed(creature, AttackType::ATTACK_TYPE_MELEE_PRIMARY));

    creature->get_equipment().remove_item(EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);
    creature->get_equipment().set_item(mw, EquipmentWornLocation::EQUIPMENT_WORN_OFF_HAND);

    EXPECT_EQ(se.second, ucc.is_attack_unarmed(creature, AttackType::ATTACK_TYPE_MELEE_SECONDARY));
    EXPECT_TRUE(ucc.is_attack_unarmed(creature, AttackType::ATTACK_TYPE_MELEE_TERTIARY_UNARMED));
  }
}

TEST(SW_Engine_Calculator_UnarmedCombatCalculator, calculate_pct_chance_free_kick)
{
  UnarmedCombatCalculator ucc;
  CreaturePtr creature = std::make_shared<Creature>();

  std::vector<std::pair<int, int>> skill_and_exp = { {0, 0}, {10, 0}, {35, 0}, {36, 1}, {59, 24}, {98, 63}, {100, 65} };

  for (const auto s_e : skill_and_exp)
  {
    creature->get_skills().set_value(SkillType::SKILL_MELEE_UNARMED, s_e.first);
    EXPECT_EQ(s_e.second, ucc.calculate_pct_chance_free_kick(creature));
  }
}
