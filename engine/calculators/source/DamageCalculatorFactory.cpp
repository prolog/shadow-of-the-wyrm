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
    case AttackType::ATTACK_TYPE_RANGED:
      calculator = std::make_shared<RangedPhysicalDamageCalculator>();
      break;
    case AttackType::ATTACK_TYPE_MELEE_PRIMARY:
    case AttackType::ATTACK_TYPE_MELEE_SECONDARY:
    case AttackType::ATTACK_TYPE_MELEE_TERTIARY_UNARMED:
      calculator = std::make_shared<PhysicalDamageCalculator>(attack_type);
      break;
    case AttackType::ATTACK_TYPE_MAGICAL:
      calculator = std::make_shared<MagicalDamageCalculator>();
      break;
    default: break;
  }

  return calculator;
}
