#include "gtest/gtest.h"
#include "Weapon.hpp"

TEST(SW_Engine_Calculators_MagicToHitCalculator, get_statistic)
{
	CreaturePtr creature = std::make_shared<Creature>();
	Statistic intl(25);
	intl.set_max(CreatureConstants::MAX_CREATURE_PRIMARY_STATISTIC_VALUE);

	creature->set_intelligence(intl);

	MagicToHitCalculator mthc;
	Statistic intl2(mthc.get_statistic(creature));
	EXPECT_EQ(intl, intl2);
}

TEST(SW_Engine_Calculators_MagicToHitCalculator, calculate_BAC_part)
{
	MagicToHitCalculator mthc;
	CreaturePtr creature = std::make_shared<Creature>();
	creature->set_intelligence(10);

	Blood b;
	b.set_litres(20);
	b.set_grams_alcohol(100);
	float bac = b.get_blood_alcohol_content();
	creature->set_blood(b);

	int val = mthc.calculate(creature);
	int est_intval = static_cast<int>(bac * -100);

	EXPECT_EQ(est_intval, val);
}

TEST(SW_Engine_Calculators_MagicToHitCalculator, calculate_level_part)
{
	MagicToHitCalculator mthc;
	CreaturePtr creature = std::make_shared<Creature>();
	creature->set_intelligence(10);
	creature->set_level(33);

	EXPECT_EQ(16, mthc.calculate(creature));
}

TEST(SW_Engine_Calculators_MagicToHitCalculator, calculate_magic_part)
{
	MagicToHitCalculator mthc;
	CreaturePtr creature = std::make_shared<Creature>();
	creature->set_intelligence(10);
	creature->get_skills().set_value(SkillType::SKILL_GENERAL_MAGIC, 15);

	EXPECT_EQ(3, mthc.calculate(creature));
}

TEST(SW_Engine_Calculators_MagicToHitCalculator, calculate_intelligence_part)
{
	MagicToHitCalculator mthc;
	CreaturePtr creature = std::make_shared<Creature>();
	creature->set_intelligence(25);

	EXPECT_EQ(5, mthc.calculate(creature));
}

TEST(SW_Engine_Calculators_MagicToHitCalculator, calculate_skills_part)
{
	MagicToHitCalculator mthc;
	CreaturePtr creature = std::make_shared<Creature>();
	creature->set_intelligence(10);

	EXPECT_EQ(0, mthc.calculate(creature));

	Status s;
	s.set_value(true);

	creature->set_status(StatusIdentifiers::STATUS_ID_BLINDED, s);

	std::map<int, int> bf_values = { {3, 0}, {4, 1}, {20, 5}, {44, 11}, {100, 25} };

	for (const auto& bf_pair : bf_values)
	{
		creature->get_skills().set_value(SkillType::SKILL_GENERAL_BLIND_FIGHTING, bf_pair.first);
		EXPECT_EQ(bf_pair.second, mthc.calculate(creature));
	}
}

TEST(SW_Engine_Calculators_MagicToHitCalculator, calculate_modifier_part)
{
	MagicToHitCalculator mthc;
	CreaturePtr creature = std::make_shared<Creature>();
	creature->set_intelligence(10);

	std::map<double, std::vector<std::pair<std::string, Modifier>>> modifiers;
	Modifier m;
	m.set_to_hit_modifier(13);
	modifiers[7.0] = { {"fdsa", m} };
	creature->set_modifiers(modifiers);

	EXPECT_EQ(13, mthc.calculate(creature));
}

TEST(SW_Engine_Calculators_MagicToHitCalculator, calculate_weight_part)
{
	MagicToHitCalculator mthc;
	CreaturePtr creature = std::make_shared<Creature>();
	creature->set_intelligence(10);

	MeleeWeaponPtr melee = std::make_shared<MeleeWeapon>();
	melee->set_trained_skill(SkillType::SKILL_MELEE_DAGGERS);
	creature->get_equipment().set_item(melee, EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);

	CarryingCapacityCalculator ccc;
	int burdened_limit = ccc.calculate_burdened_weight(creature);
	Weight weight;
	weight.set_weight(static_cast<uint>(burdened_limit * 2));
	melee->set_weight(weight);
	int attacker_weight_value = 0;
	int creature_carried_weight = creature->get_weight_carried();

	if (creature_carried_weight > burdened_limit)
	{
		attacker_weight_value = static_cast<int>((creature_carried_weight - burdened_limit) / 16 /* oz to lbs */ / 2);
		attacker_weight_value *= -1;
	}

	EXPECT_EQ(attacker_weight_value, mthc.calculate(creature));
}
