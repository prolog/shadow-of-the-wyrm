#include "gtest/gtest.h"

TEST(SW_World_Material_Ivory, type)
{
  Ivory i;
  EXPECT_EQ(MaterialType::MATERIAL_TYPE_IVORY, i.get_type());
}

TEST(SW_World_Material_Ivory, get_colour)
{
  Ivory i;

  EXPECT_EQ(Colour::COLOUR_BOLD_WHITE, i.get_colour());
}

TEST(SW_World_Material_Ivory, flags)
{
  Ivory i;

  EXPECT_FALSE(i.get_is_flammable());
  EXPECT_FALSE(i.get_is_explosive());
  EXPECT_FALSE(i.get_is_corrodible());
  EXPECT_FALSE(i.get_crumbles());
}

TEST(SW_World_Material_Ivory, get_material_floats)
{
  Ivory i;

  EXPECT_FALSE(i.get_material_floats());
}
