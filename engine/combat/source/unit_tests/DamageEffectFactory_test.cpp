#include "gtest/gtest.h"

TEST(SL_Engine_Combat_DamageEffectFactory, no_null_damage_effects)
{
  for (int i = DAMAGE_TYPE_SLASH; i < DAMAGE_TYPE_MAX; i++)
  {
    IDamageEffectPtr effect = DamageEffectFactory::create_damage_effect(static_cast<DamageType>(i));

    EXPECT_TRUE(effect);
  }
}

