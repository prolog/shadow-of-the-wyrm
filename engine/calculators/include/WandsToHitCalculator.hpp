#pragma once
#include "ToHitCalculator.hpp"

class WandsToHitCalculator : public ToHitCalculator
{
  public:
    WandsToHitCalculator();
    virtual ~WandsToHitCalculator() = default;

    int calculate(CreaturePtr creature) override;
    Statistic& get_statistic(CreaturePtr creature) override;
};
