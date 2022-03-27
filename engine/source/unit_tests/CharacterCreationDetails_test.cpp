#include "gtest/gtest.h"

TEST(SW_Engine_CharacterCreationDetails, default_constructor)
{
  CharacterCreationDetails ccd;
  StartingLocation sl;

  EXPECT_EQ(CreatureSex::CREATURE_SEX_NOT_SPECIFIED, ccd.get_sex());
  EXPECT_EQ(HairColour::HAIR_NA, ccd.get_hair_colour());
  EXPECT_EQ(EyeColour::EYE_COLOUR_NA, ccd.get_eye_colour());
  EXPECT_EQ("", ccd.get_race_id());
  EXPECT_EQ("", ccd.get_class_id());
  EXPECT_EQ("", ccd.get_deity_id());
  EXPECT_EQ(sl, ccd.get_starting_location());
}

TEST(SW_Engine_CharacterCreationDetails, populating_constructor)
{
  StartingLocation sl("abc", make_pair(3,4), "short_desc", "desc");
  CharacterCreationDetails ccd(CreatureSex::CREATURE_SEX_FEMALE, HairColour::HAIR_COLOUR_GREY, EyeColour::EYE_COLOUR_GREEN, 300, "elf", "mason", "the_one_god", sl);

  EXPECT_EQ(CreatureSex::CREATURE_SEX_FEMALE, ccd.get_sex());
  EXPECT_EQ(HairColour::HAIR_COLOUR_GREY, ccd.get_hair_colour());
  EXPECT_EQ(EyeColour::EYE_COLOUR_GREEN, ccd.get_eye_colour());
  EXPECT_EQ(300, ccd.get_age());
  EXPECT_EQ("elf", ccd.get_race_id());
  EXPECT_EQ("mason", ccd.get_class_id());
  EXPECT_EQ("the_one_god", ccd.get_deity_id());
  EXPECT_EQ(sl, ccd.get_starting_location());
}
