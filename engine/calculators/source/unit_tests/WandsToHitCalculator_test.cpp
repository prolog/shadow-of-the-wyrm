#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_WandsToHitCalculator, get_statistic)
{
	CreaturePtr creature = std::make_shared<Creature>();
	Statistic cha(40);
	cha.set_max(CreatureConstants::MAX_CREATURE_PRIMARY_STATISTIC_VALUE);

	creature->set_charisma(cha);

	WandsToHitCalculator wthc;
	Statistic cha2(wthc.get_statistic(creature));
	EXPECT_EQ(cha, cha2);
}

TEST(SW_Engine_Calculators_WandsToHitCalculator, calculate_BAC_part)
{
	WandsToHitCalculator wthc;
	CreaturePtr creature = std::make_shared<Creature>();
	creature->set_charisma(10);
	
	Blood b;
	b.set_litres(20);
	b.set_grams_alcohol(100);
	float bac = b.get_blood_alcohol_content();
	creature->set_blood(b);

	int val = wthc.calculate(creature);
	int est_intval = static_cast<int>(bac * -100);

	EXPECT_EQ(est_intval, val);
}

TEST(SW_Engine_Calculators_WandsToHitCalculator, calculate_level_part)
{
	WandsToHitCalculator wthc;
	CreaturePtr creature = std::make_shared<Creature>();
	creature->set_charisma(10);
	creature->set_level(8);

	EXPECT_EQ(4, wthc.calculate(creature));
}

TEST(SW_Engine_Calculators_WandsToHitCalculator, calculate_wandcraft_part)
{
	WandsToHitCalculator wthc;
	CreaturePtr creature = std::make_shared<Creature>();
	creature->set_charisma(10);
	creature->get_skills().set_value(SkillType::SKILL_GENERAL_WANDCRAFT, 50);

	EXPECT_EQ(10, wthc.calculate(creature));
}

TEST(SW_Engine_Calculators_WandsToHitCalculator, calculate_charisma_part)
{
	WandsToHitCalculator wthc;
	CreaturePtr creature = std::make_shared<Creature>();
	creature->set_charisma(1);

	EXPECT_EQ(-3, wthc.calculate(creature));

	creature->set_charisma(43);

	EXPECT_EQ(11, wthc.calculate(creature));
}

TEST(SW_Engine_Calculators_WandsToHitCalculator, calculate_modifiers_part)
{
	WandsToHitCalculator wthc;
	CreaturePtr creature = std::make_shared<Creature>();
	creature->set_charisma(10);
	
	std::map<double, std::vector<std::pair<std::string, Modifier>>> modifiers;
	Modifier m;
	m.set_to_hit_modifier(12);
	modifiers[3.0] = { {"fdsa", m} };
	creature->set_modifiers(modifiers);

	EXPECT_EQ(12, wthc.calculate(creature));
}
