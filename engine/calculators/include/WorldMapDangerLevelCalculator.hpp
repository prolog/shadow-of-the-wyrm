#pragma once
#include "DangerLevelCalculator.hpp"

class WorldMapDangerLevelCalculator : public DangerLevelCalculator
{
  public:
    int calculate(MapPtr old_map, MapPtr new_map) const override;
};

