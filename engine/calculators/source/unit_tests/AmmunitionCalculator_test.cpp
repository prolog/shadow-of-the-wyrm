#include "gtest/gtest.h"
#include "Ammunition.hpp"

TEST(SW_Engine_Calculator, calculate_stack_sizes)
{
	AmmunitionCalculator ac;
	ItemPtr ammo = std::make_shared<Ammunition>();
	Weight weight;

	std::map<uint, std::pair<int, int>> exp_stack_sizes = { {20, {1, 50}}, {24, {1, 50}}, {33, {1, 20}}, {96, {1, 20}}, {149, {1, 8}}, {1700, {1, 3}} };

	for (const auto& s_pair : exp_stack_sizes)
	{
		weight.set_weight(s_pair.first);
		ammo->set_weight(weight);

		EXPECT_EQ(s_pair.second, ac.calculate_stack_size(ammo));
	}
}

TEST(SW_Engine_Calculator, calculate_pct_chance_survival)
{
	AmmunitionCalculator ac;
	CreaturePtr creature = std::make_shared<Creature>();
	ItemPtr ammo = std::make_shared<Ammunition>();

	// Check base % chance survival
	EXPECT_EQ(40, ac.calculate_pct_chance_survival(creature, ammo));

	// Check archery: +1 for every 2 pts
	creature->get_skills().set_value(SkillType::SKILL_GENERAL_ARCHERY, 11);
	EXPECT_EQ(45, ac.calculate_pct_chance_survival(creature, ammo));

	// Check weight: +1 for every 6 oz
	Weight w;
	w.set_weight(60);
	ammo->set_weight(w);

	EXPECT_EQ(55, ac.calculate_pct_chance_survival(creature, ammo));
}

TEST(SW_Engine_Calculators_AmmunitionCalculator, slays_survival_modifier)
{
	AmmunitionCalculator ac;
	AmmunitionPtr ammo = std::make_shared<Ammunition>();

	EXPECT_EQ(0, ac.get_slays_survival_modifier(ammo));

	Damage damage;
	damage.set_slays_races({ "a", "b", "c" });
	ammo->set_damage(damage);

	EXPECT_EQ(25, ac.get_slays_survival_modifier(ammo));
}

TEST(SW_Engine_Calculators_AmmunitionCalculator, item_status_survival_modifier)
{
	AmmunitionCalculator ac;
	AmmunitionPtr ammo = std::make_shared<Ammunition>();
	std::map<ItemStatus, int> mods = { {ItemStatus::ITEM_STATUS_CURSED, -20}, {ItemStatus::ITEM_STATUS_UNCURSED, 0}, {ItemStatus::ITEM_STATUS_BLESSED, 25} };

	for (const auto& m_pair : mods)
	{
		ammo->set_status(m_pair.first);
		EXPECT_EQ(m_pair.second, ac.get_item_status_survival_modifier(ammo));
	}
}
