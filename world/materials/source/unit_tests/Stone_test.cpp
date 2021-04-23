#include "gtest/gtest.h"

TEST(SW_World_Material_Stone, type)
{
  Stone s;
  EXPECT_EQ(MaterialType::MATERIAL_TYPE_STONE, s.get_type());
}

TEST(SW_World_Material_Stone, flags)
{
  Stone s;

  EXPECT_FALSE(s.get_is_flammable());
  EXPECT_FALSE(s.get_is_explosive());
  EXPECT_FALSE(s.get_is_corrodible());
  EXPECT_TRUE(s.get_crumbles());
}

TEST(SW_World_Material_Stone, get_material_floats)
{
  Stone s;

  EXPECT_FALSE(s.get_material_floats());
}
