#pragma once
#include "ToHitCalculator.hpp"

class HeavyWeaponToHitCalculator : public ToHitCalculator
{
  public:
    HeavyWeaponToHitCalculator();
    HeavyWeaponToHitCalculator(const AttackType attack_type);
    Statistic& get_statistic(CreaturePtr creature) override;

    int calculate(CreaturePtr creature) override;
};
