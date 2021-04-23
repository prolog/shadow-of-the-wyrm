#include "gtest/gtest.h"

TEST(SW_World_Material_Cloth, type)
{
  Cloth c;
  EXPECT_EQ(MaterialType::MATERIAL_TYPE_CLOTH, c.get_type());
}

TEST(SW_World_Material_Cloth, get_colour)
{
  Cloth c;

  EXPECT_EQ(Colour::COLOUR_GREEN, c.get_colour());
}

TEST(SW_World_Material_Cloth, flags)
{
  Cloth c;

  EXPECT_TRUE(c.get_is_flammable());
  EXPECT_FALSE(c.get_is_explosive());
  EXPECT_TRUE(c.get_is_corrodible());
  EXPECT_FALSE(c.get_crumbles());
}

TEST(SW_World_Material_Cloth, get_material_floats)
{
  Cloth c;

  EXPECT_FALSE(c.get_material_floats());
}
