#pragma once
#include "Effect.hpp"
#include "EffectTypes.hpp"
#include "Modifier.hpp"
class EffectFactory
{
  public:
    static EffectPtr create_effect(const EffectType effect_type, Modifier m = Modifier(), std::map<std::string, std::string> = {}, std::string spell_id = "");

  protected:
    EffectFactory();
    ~EffectFactory();
};
