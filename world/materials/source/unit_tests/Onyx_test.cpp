#include "gtest/gtest.h"

TEST(SW_World_Material_Onyx, type)
{
  Onyx o;
  EXPECT_EQ(MaterialType::MATERIAL_TYPE_ONYX, o.get_type());
}

TEST(SW_World_Material_Onyx, get_colour)
{
  Onyx o;

  EXPECT_EQ(Colour::COLOUR_BOLD_BLACK, o.get_colour());
}

TEST(SW_World_Material_Onyx, flags)
{
  Onyx o;

  EXPECT_FALSE(o.get_is_flammable());
  EXPECT_FALSE(o.get_is_explosive());
  EXPECT_FALSE(o.get_is_corrodible());
  EXPECT_TRUE(o.get_crumbles());
}

TEST(SW_World_Material_Onyx, get_material_floats)
{
  Onyx o;

  EXPECT_FALSE(o.get_material_floats());
}
