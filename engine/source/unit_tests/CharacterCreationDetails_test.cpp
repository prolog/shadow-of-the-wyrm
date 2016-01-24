#include "gtest/gtest.h"

TEST(SW_Engine_CharacterCreationDetails, default_constructor)
{
  CharacterCreationDetails ccd;

  EXPECT_EQ(CreatureSex::CREATURE_SEX_MALE, ccd.get_sex());
  EXPECT_EQ("", ccd.get_race_id());
  EXPECT_EQ("", ccd.get_class_id());
  EXPECT_EQ("", ccd.get_deity_id());
}

TEST(SW_Engine_CharacterCreationDetails, populating_constructor)
{
  CharacterCreationDetails ccd(CreatureSex::CREATURE_SEX_FEMALE, "elf", "mason", "the_one_god");

  EXPECT_EQ(CreatureSex::CREATURE_SEX_FEMALE, ccd.get_sex());
  EXPECT_EQ("elf", ccd.get_race_id());
  EXPECT_EQ("mason", ccd.get_class_id());
  EXPECT_EQ("the_one_god", ccd.get_deity_id());
}
