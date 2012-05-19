#pragma once
#include "AttackTypes.hpp"
#include "DamageCalculator.hpp"

class DamageCalculatorFactory
{
  public:
    static DamageCalculatorPtr create_damage_calculator(const AttackType attack_type);

  protected:
    DamageCalculatorFactory();
    ~DamageCalculatorFactory();
};
