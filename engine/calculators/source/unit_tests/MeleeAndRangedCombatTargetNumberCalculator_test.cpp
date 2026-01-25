#include "gtest/gtest.h"

TEST(SW_Engine_Calculator_MeleeAndRangedCombatTargetNumberCalculator, calculate)
{
	WeaponDifficultyCalculator wdc;
	std::vector<AttackType> attack_types = { AttackType::ATTACK_TYPE_MELEE_PRIMARY,
                                           AttackType::ATTACK_TYPE_MELEE_SECONDARY,
                                           AttackType::ATTACK_TYPE_MELEE_TERTIARY_UNARMED };

	std::vector<std::string> race_ids = { RaceConstants::RACE_CONSTANTS_RACE_ID_ANIMAL, "some_other_race" };

	CreaturePtr attacking_creature = std::make_shared<Creature>();
	attacking_creature->get_skills().set_value(SkillType::SKILL_GENERAL_HUNTING, 40);
	CreaturePtr defender = std::make_shared<Creature>();
	defender->set_evade(14);

	for (const auto at : attack_types)
	{
		MeleeAndRangedCombatTargetNumberCalculator mrctnc(at);
		EXPECT_EQ(0, mrctnc.calculate(nullptr, nullptr));

		for (const auto race_id : race_ids)
		{
			defender->set_race_id(race_id);
			int hunting_bonus = 0;

			if (race_id == RaceConstants::RACE_CONSTANTS_RACE_ID_ANIMAL)
			{
				hunting_bonus = static_cast<int>(attacking_creature->get_skills().get_value(SkillType::SKILL_GENERAL_HUNTING) / 2);
			}
			
			int exp_val = wdc.calculate_base_difficulty(attacking_creature, at) -
			              hunting_bonus +
				            defender->get_evade().get_current();

			EXPECT_EQ(exp_val, mrctnc.calculate(attacking_creature, defender));
		}
	}


}

TEST(SW_Engine_Calculator_MeleeAndRangedCombatTargetNumberCalculator, calculate_pct_chance_pass_through_untargetted_square)
{
	CreaturePtr attacker = std::make_shared<Creature>();
	CreaturePtr tile_creature = std::make_shared<Creature>();

	MeleeAndRangedCombatTargetNumberCalculator mrctnc(AttackType::ATTACK_TYPE_MELEE_PRIMARY);

	EXPECT_EQ(0, mrctnc.calculate_pct_chance_pass_through_untargetted_square(nullptr, nullptr));

	Skills tc_skills;
	tc_skills.set_value(SkillType::SKILL_GENERAL_AWARENESS, 54);
	tile_creature->set_skills(tc_skills);

	EXPECT_EQ(54, mrctnc.calculate_pct_chance_pass_through_untargetted_square(nullptr, tile_creature));

	Skills a_skills;
	a_skills.set_value(SkillType::SKILL_GENERAL_ARCHERY, 30);
	attacker->set_skills(a_skills);

	EXPECT_EQ(54, mrctnc.calculate_pct_chance_pass_through_untargetted_square(attacker, tile_creature));

	attacker->get_skills().set_value(SkillType::SKILL_GENERAL_ARCHERY, 90);

	EXPECT_EQ(90, mrctnc.calculate_pct_chance_pass_through_untargetted_square(attacker, tile_creature));
}
