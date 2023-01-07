#include "gtest/gtest.h"
#include "Weapon.hpp"

TEST(SW_Engine_Calculators_LightMeleeAndRangedWeaponToHitCalculator, get_statistic)
{
	CreaturePtr creature = std::make_shared<Creature>();
	Statistic dex(6);
	dex.set_max(CreatureConstants::MAX_CREATURE_PRIMARY_STATISTIC_VALUE);

	creature->set_dexterity(dex);

	LightMeleeAndRangedWeaponToHitCalculator lmrthc;
	Statistic dex2(lmrthc.get_statistic(creature));
	EXPECT_EQ(dex, dex2);
}

TEST(SW_Engine_Calculators_LightMeleeAndRangedWeaponToHitCalculator, calculate_base_th_part)
{
	LightMeleeAndRangedWeaponToHitCalculator lmrwthc;
	CreaturePtr creature = std::make_shared<Creature>();
	creature->set_dexterity(10);
	creature->set_to_hit(16);

	EXPECT_EQ(16 + 5, lmrwthc.calculate(creature));
}

TEST(SW_Engine_Calculators_LightMeleeAndRangedWeaponToHitCalculator, calculate_nwp_part)
{
	LightMeleeAndRangedWeaponToHitCalculator lmrwthc;
	CreaturePtr creature = std::make_shared<Creature>();
	creature->set_dexterity(10);
	creature->get_skills().set_value(SkillType::SKILL_GENERAL_COMBAT, 65);

	EXPECT_EQ(13 + 5, lmrwthc.calculate(creature));
}

TEST(SW_Engine_Calculators_LightMeleeAndRangedWeaponToHitCalculator, calculate_dexterity_part)
{
	LightMeleeAndRangedWeaponToHitCalculator lmrwthc;
	CreaturePtr creature = std::make_shared<Creature>();
	creature->set_dexterity(21);

	EXPECT_EQ(3 + 5, lmrwthc.calculate(creature));
}

TEST(SW_Engine_Calculators_LightMeleeAndRangedWeaponToHitCalculator, calculate_level_part)
{
	LightMeleeAndRangedWeaponToHitCalculator lmrwthc;
	CreaturePtr creature = std::make_shared<Creature>();
	creature->set_dexterity(10);
	creature->set_level(4);

	EXPECT_EQ(2 + 5, lmrwthc.calculate(creature));
}


TEST(SW_Engine_Calculators_LightMeleeAndRangedWeaponToHitCalculator, calculate_weapon_part)
{
	LightMeleeAndRangedWeaponToHitCalculator lmrwthc;
	CreaturePtr creature = std::make_shared<Creature>();
	creature->set_dexterity(10);

	MeleeWeaponPtr melee = std::make_shared<MeleeWeapon>();
	melee->set_trained_skill(SkillType::SKILL_MELEE_DAGGERS);
	creature->get_equipment().set_item(melee, EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);
	creature->get_skills().set_value(SkillType::SKILL_MELEE_DAGGERS, 12);

	EXPECT_EQ(6, lmrwthc.calculate(creature));
}

TEST(SW_Engine_Calculators_LightMeleeAndRangedWeaponToHitCalculator, calculate_modifier_part)
{
	LightMeleeAndRangedWeaponToHitCalculator lmrwthc;
	CreaturePtr creature = std::make_shared<Creature>();
	creature->set_dexterity(10);

	std::map<double, std::vector<std::pair<std::string, Modifier>>> modifiers;
	Modifier m;
	m.set_to_hit_modifier(12);
	modifiers[3.0] = { {"fdsa", m} };
	creature->set_modifiers(modifiers);

	EXPECT_EQ(12 + 5, lmrwthc.calculate(creature));
}

TEST(SW_Engine_Calculators_LightMeleeAndRangedWeaponToHitCalculator, calculate_skill_part)
{
	LightMeleeAndRangedWeaponToHitCalculator lmrwthc;
	CreaturePtr creature = std::make_shared<Creature>();
	creature->set_dexterity(10);

	EXPECT_EQ(5, lmrwthc.calculate(creature));

	Status s;
	s.set_value(true);

	creature->set_status(StatusIdentifiers::STATUS_ID_BLINDED, s);
	
	std::map<int, int> bf_values = { {3, 0}, {4, 1}, {20, 5}, {44, 11}, {100, 25} };

	for (const auto& bf_pair : bf_values)
	{
		creature->get_skills().set_value(SkillType::SKILL_GENERAL_BLIND_FIGHTING, bf_pair.first);
		EXPECT_EQ(5 + bf_pair.second, lmrwthc.calculate(creature));
	}
}

TEST(SW_Engine_Calculators_LightMeleeAndRangedWeaponToHitCalculator, calculate_status_part)
{
	LightMeleeAndRangedWeaponToHitCalculator lmrwthc;
	CreaturePtr creature = std::make_shared<Creature>();
	creature->set_dexterity(10);

	MeleeWeaponPtr melee = std::make_shared<MeleeWeapon>();
	melee->set_trained_skill(SkillType::SKILL_MELEE_DAGGERS);
	creature->get_equipment().set_item(melee, EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);

	std::map<ItemStatus, int> st_exp = { {ItemStatus::ITEM_STATUS_CURSED, -10}, {ItemStatus::ITEM_STATUS_UNCURSED, 0}, {ItemStatus::ITEM_STATUS_BLESSED, 10} };

	for (const auto& st_exp_pair : st_exp)
	{
		melee->set_status(st_exp_pair.first);
		EXPECT_EQ(st_exp_pair.second, lmrwthc.calculate(creature));
	}
}

TEST(SW_Engine_Calculators_LightMeleeAndRangedWeaponToHitCalculator, calculate_bac_part)
{
	LightMeleeAndRangedWeaponToHitCalculator lmrwthc;
	CreaturePtr creature = std::make_shared<Creature>();
	creature->set_dexterity(10);

	Blood b;
	b.set_litres(20);
	b.set_grams_alcohol(100);
	float bac = b.get_blood_alcohol_content();
	creature->set_blood(b);

	int val = lmrwthc.calculate(creature);
	int est_intval = 5 + static_cast<int>(bac * -100);

	EXPECT_EQ(est_intval, val);
}
