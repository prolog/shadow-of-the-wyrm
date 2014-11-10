#include "gtest/gtest.h"

TEST(SL_World_Materials_MaterialFactory, output_types_not_null)
{
  for (MaterialType mt = MATERIAL_TYPE_CLOTH; mt <= MATERIAL_TYPE_GOLD; mt++)
  {
    MaterialPtr material = MaterialFactory::create_material(mt);

    EXPECT_TRUE(material != NULL);
  }
}

TEST(SL_World_Materials_MaterialFactory, output_types_match_input)
{
  for (MaterialType mt = MATERIAL_TYPE_CLOTH; mt < MATERIAL_TYPE_LAST; mt++)
  {
    MaterialPtr material = MaterialFactory::create_material(mt);

    if (material)
    {
      MaterialType mt_output = material->get_type();
      EXPECT_EQ(mt, mt_output);
    }
  }
}
