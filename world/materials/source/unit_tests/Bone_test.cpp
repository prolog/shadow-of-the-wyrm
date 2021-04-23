#include "gtest/gtest.h"

TEST(SW_World_Material_Bone, type)
{
  Bone b;
  EXPECT_EQ(MaterialType::MATERIAL_TYPE_BONE, b.get_type());
}

TEST(SW_World_Material_Bone, get_colour)
{
  Bone b;

  EXPECT_EQ(Colour::COLOUR_BOLD_WHITE, b.get_colour());
}

TEST(SW_World_Material_Bone, flags)
{
  Bone b;

  EXPECT_FALSE(b.get_is_flammable());
  EXPECT_FALSE(b.get_is_explosive());
  EXPECT_TRUE(b.get_is_corrodible());
  EXPECT_FALSE(b.get_crumbles());
}

TEST(SW_World_Material_Bone, get_material_floats)
{
  Bone b;

  EXPECT_FALSE(b.get_material_floats());
}
