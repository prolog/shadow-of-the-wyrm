#include "gtest/gtest.h"

TEST(SW_World_Material_DragonScale, type)
{
  DragonScale ds;
  EXPECT_EQ(MaterialType::MATERIAL_TYPE_DRAGON_SCALE, ds.get_type());
}

TEST(SW_World_Material_DragonScale, get_colour)
{
  DragonScale ds;

  EXPECT_EQ(Colour::COLOUR_BOLD_RED, ds.get_colour());
}

TEST(SW_World_Material_DragonScale, flags)
{
  DragonScale ds;

  EXPECT_FALSE(ds.get_is_flammable());
  EXPECT_FALSE(ds.get_is_explosive());
  EXPECT_FALSE(ds.get_is_corrodible());
  EXPECT_FALSE(ds.get_crumbles());
}

TEST(SW_World_Material_DragonScale, get_material_floats)
{
  DragonScale ds;

  EXPECT_FALSE(ds.get_material_floats());
}
