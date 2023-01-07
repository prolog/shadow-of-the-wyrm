#include "gtest/gtest.h"
#include "Weapon.hpp"

TEST(SW_Engine_Calculators_HeavyWeaponToHitCalculator, get_statistic)
{
	CreaturePtr creature = std::make_shared<Creature>();
	Statistic str(33);
	str.set_max(CreatureConstants::MAX_CREATURE_PRIMARY_STATISTIC_VALUE);

	creature->set_strength(str);

	HeavyWeaponToHitCalculator hwthc;
	Statistic str2(hwthc.get_statistic(creature));
	EXPECT_EQ(str, str2);
}

TEST(SW_Engine_Calculators_HeavyWeaponToHitCalculator, calculate_base_th)
{
	CreaturePtr creature = std::make_shared<Creature>();
	HeavyWeaponToHitCalculator hwthc;
	creature->set_strength(10);
	creature->set_to_hit(13);

	EXPECT_EQ(13 + 5, hwthc.calculate(creature));
}

TEST(SW_Engine_Calculators_HeavyWeaponToHitCalculator, calculate_combat_part)
{
	CreaturePtr creature = std::make_shared<Creature>();
	HeavyWeaponToHitCalculator hwthc;
	creature->set_strength(10);
	creature->get_skills().set_value(SkillType::SKILL_GENERAL_COMBAT, 60);

	EXPECT_EQ(12 /* combat bonus */ + 5 /* unarmed bonus */, hwthc.calculate(creature));
}

TEST(SW_Engine_Calculators_HeavyWeaponToHitCalculator, calculate_strength_part)
{
	CreaturePtr creature = std::make_shared<Creature>();
	HeavyWeaponToHitCalculator hwthc;
	creature->set_strength(54);

	EXPECT_EQ(11 /* str */ + 5 /* unarmed status bonus */, hwthc.calculate(creature));
}

TEST(SW_Engine_Calculators_HeavyWeaponToHitCalculator, calculate_level_part)
{
	CreaturePtr creature = std::make_shared<Creature>();
	HeavyWeaponToHitCalculator hwthc;
	creature->set_strength(10);
	creature->set_level(44);

	EXPECT_EQ(22 + 5, hwthc.calculate(creature));
}

TEST(SW_Engine_Calculators_HeavyWeaponToHitCalculator, calculate_weapon_part)
{
	CreaturePtr creature = std::make_shared<Creature>();
	HeavyWeaponToHitCalculator hwthc;
	creature->set_strength(10);

	MeleeWeaponPtr whip = std::make_shared<MeleeWeapon>();
	whip->set_trained_skill(SkillType::SKILL_MELEE_WHIPS);
	creature->get_equipment().set_item(whip, EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);
	creature->get_skills().set_value(SkillType::SKILL_MELEE_WHIPS, 30);

	EXPECT_EQ(15, hwthc.calculate(creature));
}

TEST(SW_Engine_Calculators_HeavyWeaponToHitCalculator, calculate_skills_part)
{
	CreaturePtr creature = std::make_shared<Creature>();
	HeavyWeaponToHitCalculator hwthc;
	creature->set_strength(10);

	std::vector<std::pair<int, int>> bf_vals = { {0, 0}, {20, 5}, {80, 20} };
	Status status;
	status.set_value(true);
	creature->set_status(StatusIdentifiers::STATUS_ID_BLINDED, status);
	
	for (const auto& bf_p : bf_vals)
	{
		creature->get_skills().set_value(SkillType::SKILL_GENERAL_BLIND_FIGHTING, bf_p.first);
		EXPECT_EQ(bf_p.second + 5, hwthc.calculate(creature));
	}
}

TEST(SW_Engine_Calculators_HeavyWeaponToHitCalculator, calculate_status_part)
{
	CreaturePtr creature = std::make_shared<Creature>();
	HeavyWeaponToHitCalculator hwthc;
	creature->set_strength(10);

	MeleeWeaponPtr whip = std::make_shared<MeleeWeapon>();
	whip->set_trained_skill(SkillType::SKILL_MELEE_WHIPS);
	creature->get_equipment().set_item(whip, EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);

	whip->set_status(ItemStatus::ITEM_STATUS_CURSED);
	EXPECT_EQ(-10, hwthc.calculate(creature));

	whip->set_status(ItemStatus::ITEM_STATUS_UNCURSED);
	EXPECT_EQ(0, hwthc.calculate(creature));

	whip->set_status(ItemStatus::ITEM_STATUS_BLESSED);
	EXPECT_EQ(10, hwthc.calculate(creature));
}
