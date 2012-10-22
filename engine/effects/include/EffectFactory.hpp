#pragma once
#include "Effect.hpp"
#include "EffectTypes.hpp"

class EffectFactory
{
  public:
    static EffectPtr create_effect(const EffectType effect_type);

  protected:
    EffectFactory();
    ~EffectFactory();
};
