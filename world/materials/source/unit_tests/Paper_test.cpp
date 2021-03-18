#include "gtest/gtest.h"

TEST(SW_World_Material_Paper, type)
{
  Paper p;
  EXPECT_EQ(MaterialType::MATERIAL_TYPE_PAPER, p.get_type());
}

TEST(SW_World_Material_Paper, get_colour)
{
  Paper p;

  EXPECT_EQ(Colour::COLOUR_BOLD_WHITE, p.get_colour());
}

TEST(SW_World_Material_Paper, flags)
{
  Paper p;

  EXPECT_TRUE(p.get_is_flammable());
  EXPECT_FALSE(p.get_is_explosive());
  EXPECT_TRUE(p.get_is_corrodible());
  EXPECT_FALSE(p.get_crumbles());
}

TEST(SW_World_Material_Paper, get_material_floats)
{
  Paper p;

  EXPECT_FALSE(p.get_material_floats());
}
