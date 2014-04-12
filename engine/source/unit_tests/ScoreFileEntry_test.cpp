#include "gtest/gtest.h"

TEST(SL_Engine_ScoreFileEntry, serialization_id)
{
  ScoreFileEntry sfe;

  EXPECT_EQ(CLASS_ID_SCORE_FILE_ENTRY, sfe.get_class_identifier());
}

TEST(SL_Engine_ScoreFileEntry, saveload)
{
  ScoreFileEntry sfe(123456, "Julian", CREATURE_SEX_MALE, true, 25, "HumanNerd");

  ostringstream oss;

  sfe.serialize(oss);

  istringstream iss(oss.str());

  ScoreFileEntry sfe2;

  sfe2.deserialize(iss);

  EXPECT_EQ(123456, sfe2.get_score());
  EXPECT_EQ("Julian", sfe2.get_name());
  EXPECT_EQ(25, sfe2.get_level());
  EXPECT_EQ("HumanNerd", sfe2.get_race_class_abrv());
  EXPECT_EQ(CREATURE_SEX_MALE, sfe2.get_sex());
}

