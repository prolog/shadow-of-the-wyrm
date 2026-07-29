#include "gtest/gtest.h"

TEST(SW_World_Material_Water, type)
{
  Water w;
  EXPECT_EQ(MaterialType::MATERIAL_TYPE_WATER, w.get_type());
}

TEST(SW_World_Material_Water, get_colour)
{
  Water w;

  EXPECT_EQ(Colour::COLOUR_BOLD_WHITE, w.get_colour());
}

TEST(SW_World_Material_WATER, flags)
{
  Water w;

  EXPECT_FALSE(w.get_is_flammable());
  EXPECT_FALSE(w.get_is_explosive());
  EXPECT_FALSE(w.get_is_corrodible());
  EXPECT_FALSE(w.get_crumbles());
}
