#include "gtest/gtest.h"

TEST(SW_World_Material_Steel, type)
{
  Steel s;
  EXPECT_EQ(MaterialType::MATERIAL_TYPE_STEEL, s.get_type());
}

TEST(SW_World_Material_Steel, flags)
{
  Steel s;

  EXPECT_FALSE(s.get_is_flammable());
  EXPECT_FALSE(s.get_is_explosive());
  EXPECT_FALSE(s.get_is_corrodible());
  EXPECT_FALSE(s.get_crumbles());
}

TEST(SW_World_Material_Steel, get_material_floats)
{
  Steel s;

  EXPECT_FALSE(s.get_material_floats());
}
