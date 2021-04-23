#include "gtest/gtest.h"

TEST(SW_World_Material_Marble, type)
{
  Marble m;
  EXPECT_EQ(MaterialType::MATERIAL_TYPE_MARBLE, m.get_type());
}

TEST(SW_World_Material_Marble, get_colour)
{
  Marble m;

  EXPECT_EQ(Colour::COLOUR_BOLD_WHITE, m.get_colour());
}

TEST(SW_World_Material_Marble, flags)
{
  Marble m;

  EXPECT_FALSE(m.get_is_flammable());
  EXPECT_FALSE(m.get_is_explosive());
  EXPECT_FALSE(m.get_is_corrodible());
  EXPECT_TRUE(m.get_crumbles());
}

TEST(SW_World_Material_Marble, get_material_floats)
{
  Marble m;

  EXPECT_FALSE(m.get_material_floats());
}
