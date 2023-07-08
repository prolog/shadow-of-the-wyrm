#include "gtest/gtest.h"

TEST(SW_World_Material_Plant, type)
{
  PlantMaterial p;
  EXPECT_EQ(MaterialType::MATERIAL_TYPE_PLANT, p.get_type());
}

TEST(SW_World_Material_Plant, get_colour)
{
  PlantMaterial p;

  EXPECT_EQ(Colour::COLOUR_BOLD_GREEN, p.get_colour());
}

TEST(SW_World_Material_Plant, flags)
{
  PlantMaterial p;

  EXPECT_TRUE(p.get_is_flammable());
  EXPECT_FALSE(p.get_is_explosive());
  EXPECT_TRUE(p.get_is_corrodible());
  EXPECT_FALSE(p.get_crumbles());
}

TEST(SW_World_Material_Plant, get_material_floats)
{
  PlantMaterial p;

  EXPECT_TRUE(p.get_material_floats());
}

