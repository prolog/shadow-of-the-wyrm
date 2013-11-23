#include "MagicalAttackSpeedCalculator.hpp"
#include "NullSpeedCalculator.hpp"
#include "PrimaryPhysicalAttackSpeedCalculator.hpp"
#include "RangedAttackSpeedCalculator.hpp"
#include "SecondaryPhysicalAttackSpeedCalculator.hpp"
#include "SpeedCalculatorFactory.hpp"

SpeedCalculatorFactory::SpeedCalculatorFactory()
{
}

SpeedCalculatorFactory::~SpeedCalculatorFactory()
{
}

// Create a speed calculator based on the attack type
ISpeedCalculatorPtr SpeedCalculatorFactory::create_speed_calculator(const AttackType attack_type)
{
  ISpeedCalculatorPtr speed_calculator;

  switch(attack_type)
  {
    case ATTACK_TYPE_MELEE_PRIMARY:
      speed_calculator = std::make_shared<PrimaryPhysicalAttackSpeedCalculator>();
      break;
    case ATTACK_TYPE_MELEE_SECONDARY:
      speed_calculator = std::make_shared<SecondaryPhysicalAttackSpeedCalculator>();
      break;
    case ATTACK_TYPE_RANGED:
      speed_calculator = std::make_shared<RangedAttackSpeedCalculator>();
      break;
    case ATTACK_TYPE_MAGICAL:
    default:
      speed_calculator = std::make_shared<MagicalAttackSpeedCalculator>();
      break;
  }

  return speed_calculator;
}

