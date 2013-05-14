#pragma once
#include "gtest/gtest.h"

TEST(SL_Engine_Effects_EffectFactory, effect_types_product_valid_effect_ptr)
{
  for (int i = EFFECT_TYPE_NULL; i < EFFECT_TYPE_LAST; i++)
  {
    EffectPtr effect = EffectFactory::create_effect(static_cast<EffectType>(i));

    // Ensure a valid shared pointer was created.
    EXPECT_TRUE(effect);
  }
}
