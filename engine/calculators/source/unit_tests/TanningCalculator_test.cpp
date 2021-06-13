#include "gtest/gtest.h"

void jiggle_tanning_bonus_skills(CreaturePtr creature)
{
  if (creature != nullptr)
  {
    vector<SkillType> tanning_skills = { SkillType::SKILL_GENERAL_CRAFTING, SkillType::SKILL_GENERAL_TANNING };

    for (const auto& sk : tanning_skills)
    {
      creature->get_skills().set_value(sk, RNG::range(0, 100));
    }
  }
}
TEST(SW_Engine_Calculator_TanningCalculator, combat_min)
{
  CreaturePtr creature = std::make_shared<Creature>();
  TanningCalculator tc;

  for (int i = 0; i < 5; i++)
  {
    jiggle_tanning_bonus_skills(creature);

    int tanning_part = creature->get_skills().get_value(SkillType::SKILL_GENERAL_TANNING) / 50;
    int crafting_part = creature->get_skills().get_value(SkillType::SKILL_GENERAL_CRAFTING) / 50;

    EXPECT_EQ(tanning_part + crafting_part, tc.calculate_combat_bonus_min(creature));
  }
}

TEST(SW_Engine_Calculator_TanningCalculator, combat_max)
{
  CreaturePtr creature = std::make_shared<Creature>();
  TanningCalculator tc;

  for (int i = 0; i < 5; i++)
  {
    jiggle_tanning_bonus_skills(creature);

    int tanning_part = creature->get_skills().get_value(SkillType::SKILL_GENERAL_TANNING) / 5;
    int crafting_part = creature->get_skills().get_value(SkillType::SKILL_GENERAL_CRAFTING) / 5;

    EXPECT_EQ(tanning_part + crafting_part, tc.calculate_combat_bonus_max(creature));
  }
}

TEST(SW_Engine_Calculator_TanningCalculator, evade_min)
{
  CreaturePtr creature = std::make_shared<Creature>();
  TanningCalculator tc;

  for (int i = 0; i < 5; i++)
  {
    jiggle_tanning_bonus_skills(creature);

    int tanning_part = creature->get_skills().get_value(SkillType::SKILL_GENERAL_TANNING) / 50;
    int crafting_part = creature->get_skills().get_value(SkillType::SKILL_GENERAL_CRAFTING) / 50;

    EXPECT_EQ(tanning_part + crafting_part, tc.calculate_evade_bonus_min(creature));
  }
}

TEST(SW_Engine_Calculator_TanningCalculator, evade_max)
{
  CreaturePtr creature = std::make_shared<Creature>();
  TanningCalculator tc;

  for (int i = 0; i < 5; i++)
  {
    jiggle_tanning_bonus_skills(creature);

    int tanning_part = creature->get_skills().get_value(SkillType::SKILL_GENERAL_TANNING) / 10;
    int crafting_part = creature->get_skills().get_value(SkillType::SKILL_GENERAL_CRAFTING) / 10;

    EXPECT_EQ(tanning_part + crafting_part, tc.calculate_evade_bonus_max(creature));
  }
}

TEST(SW_Engine_Calculator_TanningCalculator, soak_min)
{
  CreaturePtr creature = std::make_shared<Creature>();
  TanningCalculator tc;

  for (int i = 0; i < 5; i++)
  {
    jiggle_tanning_bonus_skills(creature);

    int tanning_part = creature->get_skills().get_value(SkillType::SKILL_GENERAL_TANNING) / 50;
    int crafting_part = creature->get_skills().get_value(SkillType::SKILL_GENERAL_CRAFTING) / 50;

    EXPECT_EQ(tanning_part + crafting_part, tc.calculate_soak_bonus_min(creature));
  }
}

TEST(SW_Engine_Calculator_TanningCalculator, soak_max)
{
  CreaturePtr creature = std::make_shared<Creature>();
  TanningCalculator tc;

  for (int i = 0; i < 5; i++)
  {
    jiggle_tanning_bonus_skills(creature);

    int tanning_part = creature->get_skills().get_value(SkillType::SKILL_GENERAL_TANNING) / 20;
    int crafting_part = creature->get_skills().get_value(SkillType::SKILL_GENERAL_CRAFTING) / 20;

    EXPECT_EQ(tanning_part + crafting_part, tc.calculate_soak_bonus_max(creature));
  }
}
