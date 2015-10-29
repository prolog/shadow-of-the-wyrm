#pragma once
#include "AttackTypes.hpp"
#include "DamageCalculator.hpp"
#include "CalendarTypes.hpp"

class DamageCalculatorFactory
{
  public:
    static DamageCalculatorPtr create_damage_calculator(const AttackType attack_type, const PhaseOfMoonType pom_type);

  protected:
    DamageCalculatorFactory();
    ~DamageCalculatorFactory();
};
