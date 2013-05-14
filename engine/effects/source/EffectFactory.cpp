#include <boost/make_shared.hpp>
#include "EffectFactory.hpp"
#include "EtherEffect.hpp"
#include "HealingEffect.hpp"
#include "IdentifyEffect.hpp"
#include "NullEffect.hpp"
#include "FruitJuiceEffect.hpp"
#include "TeleportEffect.hpp"

using namespace std;

EffectFactory::EffectFactory()
{
}

EffectFactory::~EffectFactory()
{
}

EffectPtr EffectFactory::create_effect(const EffectType effect_type)
{
  BOOST_STATIC_ASSERT(EFFECT_TYPE_LAST == 6);

  EffectPtr effect;

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
    case EFFECT_TYPE_TELEPORT:
      effect = boost::make_shared<TeleportEffect>();
      break;
    case EFFECT_TYPE_NULL:
    default:
      effect = boost::make_shared<NullEffect>();
      break;
  }

  return effect;
}

#ifdef UNIT_TESTS
#include "unit_tests/EffectFactory_test.cpp"
#endif