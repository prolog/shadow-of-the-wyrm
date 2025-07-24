#pragma once
#include "ToHitCalculator.hpp"

class MagicToHitCalculator : public ToHitCalculator
{
  public:
    MagicToHitCalculator();
    virtual ~MagicToHitCalculator() = default;

    int calculate(CreaturePtr creature, MapPtr map) override;
    Statistic& get_statistic(CreaturePtr creature) override;

    static const int MAGIC_WEIGHT_DIVISOR;
};
