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

