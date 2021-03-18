#include "gtest/gtest.h"

TEST(SW_World_Material_Iron, type)
{
  Iron i;
  EXPECT_EQ(MaterialType::MATERIAL_TYPE_IRON, i.get_type());
}

TEST(SW_World_Material_Iron, flags)
{
  Iron i;

  EXPECT_FALSE(i.get_is_flammable());
  EXPECT_FALSE(i.get_is_explosive());
  EXPECT_FALSE(i.get_is_corrodible());
  EXPECT_FALSE(i.get_crumbles());
}

TEST(SW_World_Material_Iron, get_material_floats)
{
  Iron i;

  EXPECT_FALSE(i.get_material_floats());
}
