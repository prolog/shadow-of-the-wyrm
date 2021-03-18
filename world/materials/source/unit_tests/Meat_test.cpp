#include "gtest/gtest.h"

TEST(SW_World_Material_Meat, type)
{
  Meat m;
  EXPECT_EQ(MaterialType::MATERIAL_TYPE_MEAT, m.get_type());
}

TEST(SW_World_Material_Meat, get_colour)
{
  Meat m;

  EXPECT_EQ(Colour::COLOUR_WHITE, m.get_colour());
}

TEST(SW_World_Material_Meat, flags)
{
  Meat m;

  EXPECT_TRUE(m.get_is_flammable());
  EXPECT_FALSE(m.get_is_explosive());
  EXPECT_TRUE(m.get_is_corrodible());
  EXPECT_FALSE(m.get_crumbles());
}

TEST(SW_World_Material_Meat, get_material_floats)
{
  Meat m;

  EXPECT_FALSE(m.get_material_floats());
}
