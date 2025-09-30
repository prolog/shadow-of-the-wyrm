#include "gtest/gtest.h"

TEST(SW_Engine_Calculator_MagicalCombatTargetNumberCalculator, calculate)
{
	MagicalCombatTargetNumberCalculator mctnc;

	CreaturePtr attacker = std::make_shared<Creature>();
	Skills a_skills;

	CreaturePtr defender = std::make_shared<Creature>();
	Skills d_skills;
	
	a_skills.set_value(SkillType::SKILL_GENERAL_MAGIC, 45);
	d_skills.set_value(SkillType::SKILL_GENERAL_AWARENESS, 66);

	attacker->set_skills(a_skills);
	defender->set_skills(d_skills);
	defender->set_evade(15);

	int expected_val = 15 + 33 - 45;

	EXPECT_EQ(expected_val, mctnc.calculate(attacker, defender));
}

TEST(SW_Engine_Calculator_MagicalCombatTargetNumberCalculator, calculate_pct_chance_pass_through_untargetted_tile)
{
	MagicalCombatTargetNumberCalculator mctnc;

	EXPECT_EQ(100, mctnc.calculate_pct_chance_pass_through_untargetted_square(nullptr, nullptr));
}

TEST(SW_Engine_Calculator_MagicalCombatTargetNumberCalculator, get_attacker_skill)
{
	MagicalCombatTargetNumberCalculator mctnc;

	EXPECT_EQ(SkillType::SKILL_GENERAL_MAGIC, mctnc.get_attacker_skill());
}
