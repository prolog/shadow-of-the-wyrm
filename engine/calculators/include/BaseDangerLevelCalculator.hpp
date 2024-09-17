#pragma once
#include "DangerLevelCalculator.hpp"

class BaseDangerLevelCalculator : public DangerLevelCalculator
{
  public:
    virtual ~BaseDangerLevelCalculator() = default;

    virtual int calculate(MapPtr old_map, MapPtr new_map) const override;
};

