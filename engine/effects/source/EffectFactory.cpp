#include <boost/make_shared.hpp>
#include "EffectFactory.hpp"
#include "HealingEffect.hpp"
#include "NullEffect.hpp"

using boost::make_shared;

EffectFactory::EffectFactory()
{
}

EffectFactory::~EffectFactory()
{
}

EffectPtr EffectFactory::create_effect(const EffectType effect_type)
{
  EffectPtr effect;

  switch(effect_type)
  {
    case EFFECT_TYPE_HEALING:
      effect = make_shared<HealingEffect>();
      break;
    case EFFECT_TYPE_NULL:
    default:
      effect = make_shared<NullEffect>();
      break;
  }

  return effect;
}

