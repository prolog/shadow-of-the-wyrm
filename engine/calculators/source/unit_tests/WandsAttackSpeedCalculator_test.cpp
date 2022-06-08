#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_WandsAttackSpeedCalculator, calculate)
{
	CreaturePtr creature = std::make_shared<Creature>();
	WandsAttackSpeedCalculator wasc;

	std::map<int, int> exp_vals = { {0, 10}, {9, 10}, {10, 9}, {16, 9}, {33, 7}, {58, 5}, {99, 1}, {100, 1} };

	for (const auto& exp_pair : exp_vals)
	{
		creature->get_skills().set_value(SkillType::SKILL_GENERAL_WANDCRAFT, exp_pair.first);
		EXPECT_EQ(exp_pair.second, wasc.calculate(creature));
	}
}
