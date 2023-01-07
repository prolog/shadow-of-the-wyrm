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

DamageCalculatorPtr DamageCalculatorFactory::create_damage_calculator(const AttackType attack_type, const PhaseOfMoonType pom)
{
  DamageCalculatorPtr calculator;

  switch(attack_type)
  {
    case AttackType::ATTACK_TYPE_RANGED:
      calculator = std::make_unique<RangedPhysicalDamageCalculator>(pom);
      break;
    case AttackType::ATTACK_TYPE_MELEE_PRIMARY:
    case AttackType::ATTACK_TYPE_MELEE_SECONDARY:
    case AttackType::ATTACK_TYPE_MELEE_TERTIARY_UNARMED:
      calculator = std::make_unique<PhysicalDamageCalculator>(attack_type, pom);
      break;
    case AttackType::ATTACK_TYPE_MAGICAL:
    case AttackType::ATTACK_TYPE_MAGICAL_WANDS:
      calculator = std::make_unique<MagicalDamageCalculator>(pom);
      break;
    default: break;
  }

  return calculator;
}
