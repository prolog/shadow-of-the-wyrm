#include "gtest/gtest.h"

TEST(SW_Engine_Creatures_CreatureDifficulty, difficulty_text_sids)
{
  CreatureDifficulty cd;
  CreaturePtr c1, c2;

  c1 = CreaturePtr(new Creature());
  c2 = CreaturePtr(new Creature());

  Statistic c1_level(11);
  Statistic c2_level(1);

  c1->set_level(c1_level);
  c2->set_level(c2_level);

  EXPECT_EQ(DifficultyTextKeys::DIFFICULTY_HARMLESS, cd.get_difficulty_text_sid(c1, c2));
  
  c2_level = 5;
  c2->set_level(c2_level);

  EXPECT_EQ(DifficultyTextKeys::DIFFICULTY_EASY, cd.get_difficulty_text_sid(c1, c2));
  
  c2_level = 9;
  c2->set_level(c2_level);

  EXPECT_EQ(DifficultyTextKeys::DIFFICULTY_CAPABLE, cd.get_difficulty_text_sid(c1, c2));
  
  c2_level = 14;
  c2->set_level(c2_level);

  EXPECT_EQ(DifficultyTextKeys::DIFFICULTY_CAPABLE, cd.get_difficulty_text_sid(c1, c2));

  c2_level = 16;
  c2->set_level(c2_level);

  EXPECT_EQ(DifficultyTextKeys::DIFFICULTY_DANGEROUS, cd.get_difficulty_text_sid(c1, c2));

  c2_level = 27;
  c2->set_level(c2_level);
  
  EXPECT_EQ(DifficultyTextKeys::DIFFICULTY_DEADLY, cd.get_difficulty_text_sid(c1, c2));

  c2_level = 10000;
  c2->set_level(c2_level);

  EXPECT_EQ(DifficultyTextKeys::DIFFICULTY_DEADLY, cd.get_difficulty_text_sid(c1, c2));
}

TEST(SW_Engine_Creatures_CreatureDifficulty, hp_indicator_sids)
{
  CreaturePtr creature = std::make_shared<Creature>();
  Statistic hp(50);
  creature->set_hit_points(hp);

  CreatureDifficulty cd;

  EXPECT_EQ("", cd.get_health_indicator_sid(nullptr));
  EXPECT_EQ(DifficultyTextKeys::HP_INDICATOR_UNHARMED, cd.get_health_indicator_sid(creature));
  
  hp.set_current(45);
  creature->set_hit_points(hp);

  EXPECT_EQ(DifficultyTextKeys::HP_INDICATOR_SCRATCHES, cd.get_health_indicator_sid(creature));

  hp.set_current(28);
  creature->set_hit_points(hp);

  EXPECT_EQ(DifficultyTextKeys::HP_INDICATOR_WOUNDED, cd.get_health_indicator_sid(creature));

  hp.set_current(17);
  creature->set_hit_points(hp);

  EXPECT_EQ(DifficultyTextKeys::HP_INDICATOR_BADLY_WOUNDED, cd.get_health_indicator_sid(creature));

  hp.set_current(3);
  creature->set_hit_points(hp);

  EXPECT_EQ(DifficultyTextKeys::HP_INDICATOR_VERGE_OF_DEATH, cd.get_health_indicator_sid(creature));
}