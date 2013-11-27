#pragma once
#include "IDangerLevelCalculator.hpp"

class WorldMapDangerLevelCalculator : public IDangerLevelCalculator
{
  public:
    int calculate(MapPtr old_map, MapPtr new_map) const override;
};

