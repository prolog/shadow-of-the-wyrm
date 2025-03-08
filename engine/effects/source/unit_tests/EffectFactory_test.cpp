#pragma once
#include "gtest/gtest.h"

TEST(SW_Engine_Effects_EffectFactory, effect_types_product_valid_effect_ptr)
{
  for (int i = static_cast<int>(EffectType::EFFECT_TYPE_NULL); i < static_cast<int>(EffectType::EFFECT_TYPE_LAST); i++)
  {
    EffectPtr effect = EffectFactory::create_effect(static_cast<EffectType>(i), {}, {}, "", "");

    // Ensure a valid shared pointer was created.
    EXPECT_TRUE(effect != nullptr);
  }
}

TEST(SW_Engine_Effects_EffectFactory, status_id)
{
  std::map<EffectType, std::string> status_ids = { {EffectType::EFFECT_TYPE_FLYING, StatusIdentifiers::STATUS_ID_FLYING},
                                                   {EffectType::EFFECT_TYPE_SPEED, StatusIdentifiers::STATUS_ID_HASTE},
                                                   {EffectType::EFFECT_TYPE_RAGE, StatusIdentifiers::STATUS_ID_RAGE},
                                                   {EffectType::EFFECT_TYPE_WATER_BREATHING, StatusIdentifiers::STATUS_ID_WATER_BREATHING} };

  for (int i = static_cast<int>(EffectType::EFFECT_TYPE_NULL); i < static_cast<int>(EffectType::EFFECT_TYPE_LAST); i++)
  {
    EffectType et = static_cast<EffectType>(i);
    EffectPtr effect = EffectFactory::create_effect(et, {}, {}, "", "");

    auto s_it = status_ids.find(et);
    string expected;

    if (s_it != status_ids.end())
    {
      expected = s_it->second;
    }

    // Ensure a valid shared pointer was created.
    EXPECT_EQ(expected, effect->get_status_id());
  }
}
