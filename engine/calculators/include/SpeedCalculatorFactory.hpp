#pragma once
#include "AttackTypes.hpp"
#include "ISpeedCalculator.hpp"

class SpeedCalculatorFactory
{
  public:
    static ISpeedCalculatorPtr create_speed_calculator(const AttackType attack_type);

  protected:
    SpeedCalculatorFactory();
    ~SpeedCalculatorFactory();
};

