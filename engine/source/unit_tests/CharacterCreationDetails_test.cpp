#include "gtest/gtest.h"

TEST(SW_Engine_CharacterCreationDetails, default_constructor)
{
  CharacterCreationDetails ccd;
  StartingLocation sl;

  EXPECT_EQ(CreatureSex::CREATURE_SEX_NOT_SPECIFIED, ccd.get_sex());
  EXPECT_EQ("", ccd.get_race_id());
  EXPECT_EQ("", ccd.get_class_id());
  EXPECT_EQ("", ccd.get_deity_id());
  EXPECT_EQ(sl, ccd.get_starting_location());
}

TEST(SW_Engine_CharacterCreationDetails, populating_constructor)
{
  StartingLocation sl("abc", make_pair(3,4), "desc");
  CharacterCreationDetails ccd(CreatureSex::CREATURE_SEX_FEMALE, "elf", "mason", "the_one_god", sl);

  EXPECT_EQ(CreatureSex::CREATURE_SEX_FEMALE, ccd.get_sex());
  EXPECT_EQ("elf", ccd.get_race_id());
  EXPECT_EQ("mason", ccd.get_class_id());
  EXPECT_EQ("the_one_god", ccd.get_deity_id());
  EXPECT_EQ(sl, ccd.get_starting_location());
}
