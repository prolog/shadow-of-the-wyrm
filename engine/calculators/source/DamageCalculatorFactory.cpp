#include <boost/make_shared.hpp>
#include "DamageCalculatorFactory.hpp"
#include "MagicalDamageCalculator.hpp"
#include "PhysicalDamageCalculator.hpp"
#include "RangedPhysicalDamageCalculator.hpp"

using boost::make_shared;

DamageCalculatorFactory::DamageCalculatorFactory()
{
}

DamageCalculatorFactory::~DamageCalculatorFactory()
{
}

DamageCalculatorPtr DamageCalculatorFactory::create_damage_calculator(const AttackType attack_type)
{
  DamageCalculatorPtr calculator;

  switch(attack_type)
  {
    case ATTACK_TYPE_RANGED:
      calculator = make_shared<RangedPhysicalDamageCalculator>();
      break;
    case ATTACK_TYPE_MELEE_PRIMARY:
    case ATTACK_TYPE_MELEE_SECONDARY:
      calculator = make_shared<PhysicalDamageCalculator>(attack_type);
      break;
    case ATTACK_TYPE_MAGICAL:
      calculator = make_shared<MagicalDamageCalculator>();
      break;
    default: break;
  }

  return calculator;
}
