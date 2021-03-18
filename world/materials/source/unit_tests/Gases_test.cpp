#include "gtest/gtest.h"

TEST(SW_World_Material_Gases, type)
{
  Gases g;
  EXPECT_EQ(MaterialType::MATERIAL_TYPE_GASES, g.get_type());
}

TEST(SW_World_Material_Gases, get_colour)
{
  Gases g;

  EXPECT_EQ(Colour::COLOUR_WHITE, g.get_colour());
}

TEST(SW_World_Material_Gases, flags)
{
  Gases g;

  EXPECT_TRUE(g.get_is_flammable());
  EXPECT_TRUE(g.get_is_explosive());
  EXPECT_FALSE(g.get_is_corrodible());
  EXPECT_FALSE(g.get_crumbles());
}

TEST(SW_World_Material_Gases, get_material_floats)
{
  Gases g;

  EXPECT_TRUE(g.get_material_floats());
}
