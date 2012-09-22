#include <boost/make_shared.hpp>
#include "EffectFactory.hpp"
#include "EtherEffect.hpp"
#include "HealingEffect.hpp"
#include "IdentifyEffect.hpp"
#include "NullEffect.hpp"
#include "FruitJuiceEffect.hpp"

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

  // JCD TODO: Create a unit test for this function that iterates
  // over the range of effect types, and ensures that a null 
  // shared_ptr isn't produced.
  switch(effect_type)
  {
    case EFFECT_TYPE_HEALING:
      effect = make_shared<HealingEffect>();
      break;
    case EFFECT_TYPE_IDENTIFY:
      effect = make_shared<IdentifyEffect>();
      break;
    case EFFECT_TYPE_ETHER:
      effect = make_shared<EtherEffect>();
      break;
    case EFFECT_TYPE_FRUIT_JUICE:
      effect = make_shared<FruitJuiceEffect>();
      break;
    case EFFECT_TYPE_NULL:
    default:
      effect = make_shared<NullEffect>();
      break;
  }

  return effect;
}

