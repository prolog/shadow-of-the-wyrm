#pragma once
#include "AttackTypes.hpp"
#include "CombatTargetNumberCalculator.hpp"

class CombatTargetNumberCalculatorFactory
{
  public:
    static CombatTargetNumberCalculatorPtr create_target_number_calculator(AttackType attack_type);

  protected:
    CombatTargetNumberCalculatorFactory();
    ~CombatTargetNumberCalculatorFactory();
};
