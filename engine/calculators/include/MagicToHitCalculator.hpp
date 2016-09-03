#pragma once
#include "ToHitCalculator.hpp"

class MagicToHitCalculator : public ToHitCalculator
{
  public:
    MagicToHitCalculator();
    int calculate(CreaturePtr creature) override;
    Statistic& get_statistic(CreaturePtr creature) override;

    static const int MAGIC_WEIGHT_DIVISOR;
};
