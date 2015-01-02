#include "gtest/gtest.h"

TEST(SL_Engine_Calculators_CorpseCalculator, calculate_chance_successful_skin)
{
  CorpseCalculator cc;
  CreaturePtr creature = std::make_shared<Creature>();
  Skills skills;

  EXPECT_EQ(35, cc.calculate_chance_successful_skin(creature));

  skills.set_value(SkillType::SKILL_GENERAL_SKINNING, 1);
  creature->set_skills(skills);

  EXPECT_EQ(36, cc.calculate_chance_successful_skin(creature));

  skills.set_value(SkillType::SKILL_GENERAL_SKINNING, 22);
  creature->set_skills(skills);

  EXPECT_EQ(57, cc.calculate_chance_successful_skin(creature));

  skills.set_value(SkillType::SKILL_GENERAL_SKINNING, 100);
  creature->set_skills(skills);

  EXPECT_EQ(100, cc.calculate_chance_successful_skin(creature));
}

TEST(SL_Engine_Calculators_CorpseCalculator, calculate_chance_corpse)
{
  CorpseCalculator cc;
  CreaturePtr creature = std::make_shared<Creature>();
  Skills skills;

  EXPECT_EQ(15, cc.calculate_chance_corpse(creature));

  skills.set_value(SkillType::SKILL_GENERAL_FORAGING, 1);
  creature->set_skills(skills);

  EXPECT_EQ(15, cc.calculate_chance_corpse(creature));

  skills.set_value(SkillType::SKILL_GENERAL_FORAGING, 22);
  creature->set_skills(skills);

  EXPECT_EQ(20, cc.calculate_chance_corpse(creature));

  skills.set_value(SkillType::SKILL_GENERAL_FORAGING, 100);
  creature->set_skills(skills);

  EXPECT_EQ(40, cc.calculate_chance_corpse(creature));
}
