#include "gtest/gtest.h"

TEST(SW_World_Material_Leather, type)
{
  Leather l;
  EXPECT_EQ(MaterialType::MATERIAL_TYPE_LEATHER, l.get_type());
}

TEST(SW_World_Material_Leather, get_colour)
{
  Leather l;

  EXPECT_EQ(Colour::COLOUR_YELLOW, l.get_colour());
}

TEST(SW_World_Material_Leather, flags)
{
  Leather l;

  EXPECT_FALSE(l.get_is_flammable());
  EXPECT_FALSE(l.get_is_explosive());
  EXPECT_FALSE(l.get_is_corrodible());
  EXPECT_FALSE(l.get_crumbles());
}

TEST(SW_World_Material_Leather, get_material_floats)
{
  Leather l;

  EXPECT_TRUE(l.get_material_floats());
}
