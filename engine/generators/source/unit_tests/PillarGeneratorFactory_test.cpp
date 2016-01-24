#include "gtest/gtest.h"

TEST(SW_Engine_Generators_PillarGeneratorFactory, all_types_non_null)
{
  for (int i = 0; i < static_cast<int>(PillarType::PILLAR_TYPE_LAST); i++)
  {
    IPillarGeneratorPtr p_gen = PillarGeneratorFactory::create_generator(static_cast<PillarType>(i));

    EXPECT_TRUE(p_gen != nullptr);
  }
}

