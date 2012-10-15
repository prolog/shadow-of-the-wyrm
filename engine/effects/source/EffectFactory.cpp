#include <boost/make_shared.hpp>
#include "EffectFactory.hpp"
#include "EtherEffect.hpp"
#include "HealingEffect.hpp"
#include "IdentifyEffect.hpp"
#include "NullEffect.hpp"
#include "FruitJuiceEffect.hpp"

using namespace std;

EffectSerializationMap EffectFactory::effect_map;

EffectFactory::EffectFactory()
{
}

EffectFactory::~EffectFactory()
{
}

EffectPtr EffectFactory::create_effect(const ClassIdentifier ci)
{
  EffectPtr effect;

  if (effect_map.empty()) 
  {
    initialize_effect_map();
  }

  EffectSerializationMap::iterator e_it = effect_map.find(ci);

  if (e_it != effect_map.end())
  {
    effect = create_effect(e_it->second);
  }

  return effect;
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

void EffectFactory::initialize_effect_map()
{
  effect_map.clear();

  effect_map.insert(make_pair(CLASS_ID_ETHER_EFFECT, EFFECT_TYPE_ETHER));
  effect_map.insert(make_pair(CLASS_ID_FRUIT_JUICE_EFFECT, EFFECT_TYPE_FRUIT_JUICE));
  effect_map.insert(make_pair(CLASS_ID_HEALING_EFFECT, EFFECT_TYPE_HEALING));
  effect_map.insert(make_pair(CLASS_ID_IDENTIFY_EFFECT, EFFECT_TYPE_IDENTIFY));
  effect_map.insert(make_pair(CLASS_ID_NULL_EFFECT, EFFECT_TYPE_NULL));
}