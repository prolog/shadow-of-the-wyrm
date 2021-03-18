#include "gtest/gtest.h"

TEST(SW_World_Material_Glass, type)
{
  Glass g;
  EXPECT_EQ(MaterialType::MATERIAL_TYPE_GLASS, g.get_type());
}

TEST(SW_World_Material_Glass, flags)
{
  Glass g;

  EXPECT_FALSE(g.get_is_flammable());
  EXPECT_TRUE(g.get_is_explosive());
  EXPECT_FALSE(g.get_is_corrodible());
  EXPECT_FALSE(g.get_crumbles());
}

TEST(SW_World_Material_Glass, get_material_floats)
{
  Glass g;

  EXPECT_FALSE(g.get_material_floats());
}
