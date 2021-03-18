#include "gtest/gtest.h"

TEST(SW_World_Material_Wood, type)
{
  Wood w;
  EXPECT_EQ(MaterialType::MATERIAL_TYPE_WOOD, w.get_type());
}

TEST(SW_World_Material_Wood, get_colour)
{
  Wood w;

  EXPECT_EQ(Colour::COLOUR_YELLOW, w.get_colour());
}

TEST(SW_World_Material_Wood, flags)
{
  Wood w;

  EXPECT_TRUE(w.get_is_flammable());
  EXPECT_FALSE(w.get_is_explosive());
  EXPECT_TRUE(w.get_is_corrodible());
  EXPECT_FALSE(w.get_crumbles());
}

TEST(SW_World_Material_Wood, get_material_floats)
{
  Wood w;

  EXPECT_TRUE(w.get_material_floats());
}
