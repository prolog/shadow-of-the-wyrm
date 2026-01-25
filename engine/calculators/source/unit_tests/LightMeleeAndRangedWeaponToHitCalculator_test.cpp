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


}

TEST(SW_Engine_Calculators_LightMeleeAndRangedWeaponToHitCalculator, calculate_nwp_part)
{
	LightMeleeAndRangedWeaponToHitCalculator lmrwthc;
	CreaturePtr creature = std::make_shared<Creature>();
	creature->set_dexterity(10);
	creature->get_skills().set_value(SkillType::SKILL_GENERAL_COMBAT, 65);

	EXPECT_EQ(13 + 5, lmrwthc.calculate(creature, nullptr));
}

TEST(SW_Engine_Calculators_LightMeleeAndRangedWeaponToHitCalculator, calculate_dexterity_part)
{
	LightMeleeAndRangedWeaponToHitCalculator lmrwthc;
	CreaturePtr creature = std::make_shared<Creature>();
	creature->set_dexterity(21);

	EXPECT_EQ(3 + 5, lmrwthc.calculate(creature, nullptr));
}

TEST(SW_Engine_Calculators_LightMeleeAndRangedWeaponToHitCalculator, calculate_level_part)
{
	LightMeleeAndRangedWeaponToHitCalculator lmrwthc;
	CreaturePtr creature = std::make_shared<Creature>();
	creature->set_dexterity(10);
	creature->set_level(4);

	EXPECT_EQ(2 + 5, lmrwthc.calculate(creature, nullptr));
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

	EXPECT_EQ(6, lmrwthc.calculate(creature, nullptr));
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

	EXPECT_EQ(12 + 5, lmrwthc.calculate(creature, nullptr));
}

TEST(SW_Engine_Calculators_LightMeleeAndRangedWeaponToHitCalculator, calculate_skill_part)
{
	LightMeleeAndRangedWeaponToHitCalculator lmrwthc;
	CreaturePtr creature = std::make_shared<Creature>();
	creature->set_dexterity(10);

	EXPECT_EQ(5, lmrwthc.calculate(creature, nullptr));

	Status s;
	s.set_value(true);

	creature->set_status(StatusIdentifiers::STATUS_ID_BLINDED, s);
	
	std::map<int, int> bf_values = { {3, 0}, {4, 1}, {20, 5}, {44, 11}, {100, 25} };

	for (const auto& bf_pair : bf_values)
	{
		creature->get_skills().set_value(SkillType::SKILL_GENERAL_BLIND_FIGHTING, bf_pair.first);
		EXPECT_EQ(5 + bf_pair.second, lmrwthc.calculate(creature, nullptr));
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
		EXPECT_EQ(st_exp_pair.second, lmrwthc.calculate(creature, nullptr));
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

	int val = lmrwthc.calculate(creature, nullptr);
	int est_intval = 5 + static_cast<int>(bac * -100);

	EXPECT_EQ(est_intval, val);
}

TEST(SW_Engine_Calculators_LightMeleeAndRangedWeaponToHitCalculator, calculate_lore_part_tile_type)
{
	LightMeleeAndRangedWeaponToHitCalculator lmrwthc;
	CreaturePtr creature = std::make_shared<Creature>();
	creature->set_dexterity(10);

	Dimensions dim;
	MapPtr map = std::make_shared<Map>(dim);

	int base_est_intval = 5;
	int val = lmrwthc.calculate(creature, map);

	EXPECT_EQ(base_est_intval, val);

	// Terrain type checks
	std::map<TileType, std::pair<SkillType, int>> skill_vals = { {TileType::TILE_TYPE_FOREST, {SkillType::SKILL_GENERAL_FOREST_LORE, 15}},
																															 {TileType::TILE_TYPE_MARSH, {SkillType::SKILL_GENERAL_MARSH_LORE, 22}},
																															 {TileType::TILE_TYPE_DESERT, {SkillType::SKILL_GENERAL_DESERT_LORE, 28}},
																															 {TileType::TILE_TYPE_HILLS, {SkillType::SKILL_GENERAL_MOUNTAIN_LORE, 15}},
																															 {TileType::TILE_TYPE_MOUNTAINS, {SkillType::SKILL_GENERAL_MOUNTAIN_LORE, 15}},
																															 {TileType::TILE_TYPE_SEA, {SkillType::SKILL_GENERAL_OCEAN_LORE, 15}}
																														 };

	for (const auto s_it : skill_vals)
	{
		int sk_val = s_it.second.second;
		creature->get_skills().set_value(s_it.second.first, sk_val);
		map->set_terrain_type(s_it.first);

		EXPECT_EQ(base_est_intval + sk_val / 10, lmrwthc.calculate(creature, map));

		creature->get_skills().set_value(s_it.second.first, 0);
	}
}

TEST(SW_Engine_Calculators_LightMeleeAndRangedWeaponToHitCalculator, calculate_lore_part_terrain_type)
{
	LightMeleeAndRangedWeaponToHitCalculator lmrwthc;
	CreaturePtr creature = std::make_shared<Creature>();
	creature->set_dexterity(10);

	Dimensions dim;
	MapPtr map = std::make_shared<Map>(dim);

	int base_est_intval = 5;

	// Map type checks
	std::map<MapType, std::pair<SkillType, int>> mt_sk_vals = { {MapType::MAP_TYPE_UNDERWORLD, {SkillType::SKILL_GENERAL_DUNGEONEERING, 56}},
																															{MapType::MAP_TYPE_UNDERWATER, {SkillType::SKILL_GENERAL_OCEAN_LORE, 67}}
	};

	for (const auto mt_it : mt_sk_vals)
	{
		int sk_val = mt_it.second.second;
		creature->get_skills().set_value(mt_it.second.first, sk_val);
		map->set_map_type(mt_it.first);

		EXPECT_EQ(base_est_intval + sk_val / 10, lmrwthc.calculate(creature, map));

		creature->get_skills().set_value(mt_it.second.first, 0);
	}
}
