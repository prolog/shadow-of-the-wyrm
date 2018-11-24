#pragma once
#include "AttackTypes.hpp"
#include "AttackSpeedCalculator.hpp"

class AttackSpeedCalculatorFactory
{
  public:
    static AttackSpeedCalculatorPtr create_speed_calculator(const AttackType attack_type);

  protected:
    AttackSpeedCalculatorFactory();
    ~AttackSpeedCalculatorFactory();
};

