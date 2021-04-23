#include "gtest/gtest.h"

TEST(SW_World_Material_UnknownMaterial, type)
{
  UnknownMaterial um;
  EXPECT_EQ(MaterialType::MATERIAL_TYPE_UNKNOWN, um.get_type());
}

TEST(SW_World_Material_UnknownMaterial, get_colour)
{
  UnknownMaterial um;

  EXPECT_EQ(Colour::COLOUR_BOLD_YELLOW, um.get_colour());
}

TEST(SW_World_Material_UnknownMaterial, flags)
{
  UnknownMaterial um;

  EXPECT_FALSE(um.get_is_flammable());
  EXPECT_FALSE(um.get_is_explosive());
  EXPECT_FALSE(um.get_is_corrodible());
  EXPECT_FALSE(um.get_crumbles());
}

TEST(SW_World_Material_UnknownMaterial, get_material_floats)
{
  UnknownMaterial um;

  EXPECT_FALSE(um.get_material_floats());
}
