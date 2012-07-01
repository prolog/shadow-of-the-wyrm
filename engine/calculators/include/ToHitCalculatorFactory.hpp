#pragma once
#include "AttackTypes.hpp"
#include "ToHitCalculator.hpp"
#include "Weapon.hpp"

class ToHitCalculatorFactory
{
  public:
    static ToHitCalculatorPtr create_to_hit_calculator(CreaturePtr creature, AttackType attack_type);
    
  protected:
    static ToHitCalculatorPtr create_to_hit_calculator_given_weapon(CreatureSize creature_size, WeaponPtr weapon, const AttackType attack_type);
    
    ToHitCalculatorFactory();
    ~ToHitCalculatorFactory();
};
