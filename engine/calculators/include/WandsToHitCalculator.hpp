#pragma once
#include "ToHitCalculator.hpp"

class WandsToHitCalculator : public ToHitCalculator
{
  public:
    WandsToHitCalculator();

    int calculate(CreaturePtr creature) override;
    Statistic& get_statistic(CreaturePtr creature) override;
};
