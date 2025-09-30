#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_WandsCombatTargetNumberCalculator, calculate)
{
	WandsCombatTargetNumberCalculator wctnc;

	CreaturePtr attacker = std::make_shared<Creature>();
	Skills a_skills;

	CreaturePtr defender = std::make_shared<Creature>();
	Skills d_skills;

	a_skills.set_value(SkillType::SKILL_GENERAL_WANDCRAFT, 12);
	d_skills.set_value(SkillType::SKILL_GENERAL_AWARENESS, 80);

	attacker->set_skills(a_skills);
	defender->set_skills(d_skills);
	defender->set_evade(22);

	int expected_val = 22 + 40 - 12;

	EXPECT_EQ(expected_val, wctnc.calculate(attacker, defender));
}

TEST(SW_Engine_Calculators_WandsCombatTargetNumberCalculator, get_attacker_skill)
{
	WandsCombatTargetNumberCalculator wctnc;

	EXPECT_EQ(SkillType::SKILL_GENERAL_WANDCRAFT, wctnc.get_attacker_skill());
}