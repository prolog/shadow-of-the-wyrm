#include "gtest/gtest.h"

TEST(SL_Engine_Generators_Crypts_CryptLayoutStrategyFactory, non_null_strategies)
{
  for (int i = CRYPT_LAYOUT_PILLARS; i < CRYPT_LAYOUT_LAST; i++)
  {
    ICryptLayoutStrategyPtr layout_str = CryptLayoutStrategyFactory::create_layout_strategy(static_cast<CryptLayoutType>(i));

    EXPECT_TRUE(layout_str != nullptr);
  }
}

