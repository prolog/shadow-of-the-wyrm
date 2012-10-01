#include <boost/make_shared.hpp>
#include "EffectFactory.hpp"
#include "EtherEffect.hpp"
#include "HealingEffect.hpp"
#include "IdentifyEffect.hpp"
#include "NullEffect.hpp"
#include "FruitJuiceEffect.hpp"

EffectFactory::EffectFactory()
{
}

EffectFactory::~EffectFactory()
{
}

EffectPtr EffectFactory::create_effect(const EffectType effect_type)
{
  EffectPtr effect;

  // JCD TODO: Create a unit test for this function that iterates
  // over the range of effect types, and ensures that a null 
  // shared_ptr isn't produced.
  switch(effect_type)
  {
    case EFFECT_TYPE_HEALING:
      effect = boost::make_shared<HealingEffect>();
      break;
    case EFFECT_TYPE_IDENTIFY:
      effect = boost::make_shared<IdentifyEffect>();
      break;
    case EFFECT_TYPE_ETHER:
      effect = boost::make_shared<EtherEffect>();
      break;
    case EFFECT_TYPE_FRUIT_JUICE:
      effect = boost::make_shared<FruitJuiceEffect>();
      break;
    case EFFECT_TYPE_NULL:
    default:
      effect = boost::make_shared<NullEffect>();
      break;
  }

  return effect;
}

