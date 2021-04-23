#include "gtest/gtest.h"

TEST(SW_World_Material_Gold, type)
{
  Gold g;
  EXPECT_EQ(MaterialType::MATERIAL_TYPE_GOLD, g.get_type());
}

TEST(SW_World_Material_Gold, get_colour)
{
  Gold g;

  EXPECT_EQ(Colour::COLOUR_BOLD_YELLOW, g.get_colour());
}

TEST(SW_World_Material_Gold, flags)
{
  Gold g;

  EXPECT_FALSE(g.get_is_flammable());
  EXPECT_FALSE(g.get_is_explosive());
  EXPECT_FALSE(g.get_is_corrodible());
  EXPECT_FALSE(g.get_crumbles());
}

TEST(SW_World_Material_Gold, get_material_floats)
{
  Gold g;

  EXPECT_FALSE(g.get_material_floats());
}
