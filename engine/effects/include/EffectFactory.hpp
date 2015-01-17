#pragma once
#include "Effect.hpp"
#include "EffectTypes.hpp"
#include "StatisticsModifier.hpp"
class EffectFactory
{
  public:
    static EffectPtr create_effect(const EffectType effect_type, StatisticsModifier sm = StatisticsModifier());

  protected:
    EffectFactory();
    ~EffectFactory();
};
