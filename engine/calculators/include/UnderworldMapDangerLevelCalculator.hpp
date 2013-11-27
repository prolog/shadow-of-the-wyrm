#pragma once
#include "IDangerLevelCalculator.hpp"

class UnderworldMapDangerLevelCalculator : public IDangerLevelCalculator
{
  public:
    virtual int calculate(MapPtr old_map, MapPtr new_map) const override;
};

