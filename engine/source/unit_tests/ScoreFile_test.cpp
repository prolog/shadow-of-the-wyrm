#include "gtest/gtest.h"

TEST(SL_Engine_ScoreFile, multiple_creatures_with_same_score)
{
  ScoreFile sf(false);

  Creature c;
  CreaturePtr creature(new Creature(c));

  creature->set_experience(56);

  bool write1 = sf.write(creature);
  bool write2 = sf.write(creature);

  EXPECT_TRUE(write1);
  EXPECT_TRUE(write2);
  EXPECT_EQ(2, sf.get_entries().size());
}

