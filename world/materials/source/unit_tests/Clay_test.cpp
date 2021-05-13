#include "gtest/gtest.h"

TEST(SW_World_Material_Clay, type)
{
  Clay c;
  EXPECT_EQ(MaterialType::MATERIAL_TYPE_CLAY, c.get_type());
}

TEST(SW_World_Material_Clay, get_colour)
{
  Clay c;

  EXPECT_EQ(Colour::COLOUR_RED, c.get_colour());
}

TEST(SW_World_Material_Clay, flags)
{
  Clay c;

  EXPECT_FALSE(c.get_is_flammable());
  EXPECT_FALSE(c.get_is_explosive());
  EXPECT_FALSE(c.get_is_corrodible());
  EXPECT_TRUE(c.get_crumbles());
}

TEST(SW_World_Material_Clay, get_material_floats)
{
  Clay c;

  EXPECT_FALSE(c.get_material_floats());
}
