#pragma once
#include "IDangerLevelCalculator.hpp"

class BaseDangerLevelCalculator : public IDangerLevelCalculator
{
  public:
    virtual int calculate(MapPtr old_map, MapPtr new_map) const override;
};

