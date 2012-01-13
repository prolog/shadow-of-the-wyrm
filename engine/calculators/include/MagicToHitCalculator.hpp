#pragma once
#include "ToHitCalculator.hpp"

class MagicToHitCalculator : public ToHitCalculator
{
  public:
    MagicToHitCalculator();
    int calculate(CreaturePtr creature);
};
