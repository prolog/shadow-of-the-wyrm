#include "AttackSpeedCalculatorFactory.hpp"
#include "MagicalAttackSpeedCalculator.hpp"
#include "NullAttackSpeedCalculator.hpp"
#include "PrimaryPhysicalAttackSpeedCalculator.hpp"
#include "RangedAttackSpeedCalculator.hpp"
#include "SecondaryPhysicalAttackSpeedCalculator.hpp"
#include "TertiaryUnarmedPhysicalAttackSpeedCalculator.hpp"
#include "WandsAttackSpeedCalculator.hpp"

AttackSpeedCalculatorFactory::AttackSpeedCalculatorFactory()
{
}

AttackSpeedCalculatorFactory::~AttackSpeedCalculatorFactory()
{
}

// Create a speed calculator based on the attack type
AttackSpeedCalculatorPtr AttackSpeedCalculatorFactory::create_speed_calculator(const AttackType attack_type)
{
  AttackSpeedCalculatorPtr speed_calculator;

  switch(attack_type)
  {
    case AttackType::ATTACK_TYPE_MELEE_PRIMARY:
      speed_calculator = std::make_unique<PrimaryPhysicalAttackSpeedCalculator>();
      break;
    case AttackType::ATTACK_TYPE_MELEE_SECONDARY:
      speed_calculator = std::make_unique<SecondaryPhysicalAttackSpeedCalculator>();
      break;
    case AttackType::ATTACK_TYPE_MELEE_TERTIARY_UNARMED:
      speed_calculator = std::make_unique<TertiaryUnarmedPhysicalAttackSpeedCalculator>();
      break;
    case AttackType::ATTACK_TYPE_RANGED:
      speed_calculator = std::make_unique<RangedAttackSpeedCalculator>();
      break;
    case AttackType::ATTACK_TYPE_MAGICAL_WANDS:
      speed_calculator = std::make_unique<WandsAttackSpeedCalculator>();
      break;
    case AttackType::ATTACK_TYPE_MAGICAL:
      speed_calculator = std::make_unique<MagicalAttackSpeedCalculator>();
      break;
    default:
      speed_calculator = std::make_unique<NullAttackSpeedCalculator>();
      break;
  }

  return speed_calculator;
}

