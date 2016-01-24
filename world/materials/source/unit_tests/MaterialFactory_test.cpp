#include "gtest/gtest.h"

TEST(SW_World_Materials_MaterialFactory, output_types_not_null)
{
  for (int m = static_cast<int>(MaterialType::MATERIAL_TYPE_CLOTH); m < static_cast<int>(MaterialType::MATERIAL_TYPE_LAST); m++)
  {
    MaterialType mt = static_cast<MaterialType>(m);
    MaterialPtr material = MaterialFactory::create_material(mt);

    EXPECT_TRUE(material != NULL);
  }
}

TEST(SW_World_Materials_MaterialFactory, output_types_match_input)
{
  for (int m = static_cast<int>(MaterialType::MATERIAL_TYPE_CLOTH); m < static_cast<int>(MaterialType::MATERIAL_TYPE_LAST); m++)
  {
    MaterialType mt = static_cast<MaterialType>(m);

    MaterialPtr material = MaterialFactory::create_material(mt);

    if (material)
    {
      MaterialType mt_output = material->get_type();
      EXPECT_EQ(mt, mt_output);
    }
  }
}
