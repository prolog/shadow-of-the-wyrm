#include "gtest/gtest.h"

TEST(SW_Engine_Calculators_PacificationCalculator, calculate_pct_chance_pacify_music)
{
  CreaturePtr music_creature;
  CreaturePtr fov_creature;
  PacificationCalculator pc;
  ItemStatus status = ItemStatus::ITEM_STATUS_UNCURSED;

  EXPECT_EQ(0, pc.calculate_pct_chance_pacify_music(music_creature, fov_creature, false, status));
  EXPECT_EQ(0, pc.calculate_pct_chance_pacify_music(music_creature, fov_creature, true, status));

  music_creature = std::make_shared<Creature>();
  fov_creature = std::make_shared<Creature>();

  music_creature->get_skills().set_value(SkillType::SKILL_GENERAL_MUSIC, 30);
  music_creature->set_level(10);
  fov_creature->set_level(5);

  music_creature->set_charisma(22);
  fov_creature->set_willpower(10);

  EXPECT_EQ(39, pc.calculate_pct_chance_pacify_music(music_creature, fov_creature, false, ItemStatus::ITEM_STATUS_UNCURSED));
  EXPECT_EQ(64, pc.calculate_pct_chance_pacify_music(music_creature, fov_creature, true, ItemStatus::ITEM_STATUS_UNCURSED));

  EXPECT_EQ(19, pc.calculate_pct_chance_pacify_music(music_creature, fov_creature, false, ItemStatus::ITEM_STATUS_CURSED));
  EXPECT_EQ(44, pc.calculate_pct_chance_pacify_music(music_creature, fov_creature, true, ItemStatus::ITEM_STATUS_CURSED));

  EXPECT_EQ(59, pc.calculate_pct_chance_pacify_music(music_creature, fov_creature, false, ItemStatus::ITEM_STATUS_BLESSED));
  EXPECT_EQ(84, pc.calculate_pct_chance_pacify_music(music_creature, fov_creature, true, ItemStatus::ITEM_STATUS_BLESSED));

  fov_creature->get_skills().set_value(SkillType::SKILL_GENERAL_MUSIC, 10);

  EXPECT_EQ(29, pc.calculate_pct_chance_pacify_music(music_creature, fov_creature, false, ItemStatus::ITEM_STATUS_UNCURSED));
  EXPECT_EQ(54, pc.calculate_pct_chance_pacify_music(music_creature, fov_creature, true, ItemStatus::ITEM_STATUS_UNCURSED));

  music_creature->set_level(200);

  EXPECT_EQ(90, pc.calculate_pct_chance_pacify_music(music_creature, fov_creature, false, status));
  EXPECT_EQ(90, pc.calculate_pct_chance_pacify_music(music_creature, fov_creature, true, status));
}

