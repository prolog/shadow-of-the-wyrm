#include <boost/make_shared.hpp>
#include "DamageEffectFactory.hpp"
#include "DefaultDamageEffect.hpp"
#include "PoisonDamageEffect.hpp"

DamageEffectFactory::DamageEffectFactory()
{
}

DamageEffectFactory::~DamageEffectFactory()
{
}

IDamageEffectPtr DamageEffectFactory::create_damage_effect(const DamageType dt)
{
  IDamageEffectPtr effect;

  if (dt == DAMAGE_TYPE_POISON)
  {
    effect = boost::make_shared<PoisonDamageEffect>();
  } 
  else
  {
    effect = boost::make_shared<DefaultDamageEffect>();
  }

  return effect;
}

#ifdef UNIT_TESTS
#include "unit_tests/DamageEffectFactory_test.cpp"
#endif

