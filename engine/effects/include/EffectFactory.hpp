#pragma once
#include "Effect.hpp"
#include "EffectTypes.hpp"
#include "Modifier.hpp"

class EffectFactory
{
  public:
    static EffectPtr create_effect(const EffectType effect_type, const Modifier& m, const std::map<std::string, std::string>& properties, const std::string& spell_id, const std::string& source_id);

  protected:
    EffectFactory();
    ~EffectFactory();
};
