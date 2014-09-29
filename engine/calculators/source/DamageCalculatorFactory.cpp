#include "DamageCalculatorFactory.hpp"
#include "MagicalDamageCalculator.hpp"
#include "PhysicalDamageCalculator.hpp"
#include "RangedPhysicalDamageCalculator.hpp"

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
      calculator = std::make_shared<RangedPhysicalDamageCalculator>();
      break;
    case ATTACK_TYPE_MELEE_PRIMARY:
    case ATTACK_TYPE_MELEE_SECONDARY:
    case ATTACK_TYPE_MELEE_TERTIARY_UNARMED:
      calculator = std::make_shared<PhysicalDamageCalculator>(attack_type);
      break;
    case ATTACK_TYPE_MAGICAL:
      calculator = std::make_shared<MagicalDamageCalculator>();
      break;
    default: break;
  }

  return calculator;
}
