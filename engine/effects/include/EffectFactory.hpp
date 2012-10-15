#pragma once
#include <map>
#include "ClassIdentifiers.hpp"
#include "Effect.hpp"
#include "EffectTypes.hpp"

typedef std::map<ClassIdentifier, EffectType> EffectSerializationMap;

class EffectFactory
{
  public:
    static EffectPtr create_effect(const EffectType effect_type);
    static EffectPtr create_effect(const ClassIdentifier ci);

  protected:
    EffectFactory();
    ~EffectFactory();

    static void initialize_effect_map();

    static EffectSerializationMap effect_map;
};
