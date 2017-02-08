#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_CreateItemCalculator, calc_potential_improvement_points)
{
  CreateItemCalculator cic;
  CreaturePtr creature;

  EXPECT_EQ(0, cic.calc_potential_improvement_points(creature, SkillType::SKILL_GENERAL_BOWYER));

  creature = std::make_shared<Creature>();
  Skills& skills = creature->get_skills();

  skills.set_value(SkillType::SKILL_GENERAL_CRAFTING, 22);

  EXPECT_EQ(1, cic.calc_potential_improvement_points(creature, SkillType::SKILL_GENERAL_BOWYER));

  skills.set_value(SkillType::SKILL_GENERAL_BOWYER, 14);

  EXPECT_EQ(2, cic.calc_potential_improvement_points(creature, SkillType::SKILL_GENERAL_BOWYER));

  skills.set_value(SkillType::SKILL_GENERAL_CRAFTING, 60);
  skills.set_value(SkillType::SKILL_GENERAL_BOWYER, 50);

  EXPECT_EQ(8, cic.calc_potential_improvement_points(creature, SkillType::SKILL_GENERAL_BOWYER));

  skills.set_value(SkillType::SKILL_GENERAL_CRAFTING, 100);
  skills.set_value(SkillType::SKILL_GENERAL_BOWYER, 100);

  EXPECT_EQ(15, cic.calc_potential_improvement_points(creature, SkillType::SKILL_GENERAL_BOWYER));
}

