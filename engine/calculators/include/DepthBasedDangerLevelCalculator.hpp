#pragma once
#include "IDangerLevelCalculator.hpp"

class DepthBasedDangerLevelCalculator : public IDangerLevelCalculator
{
  public:
    DepthBasedDangerLevelCalculator(const ExitMovementType new_emt);
    virtual int calculate(MapPtr old_map, MapPtr new_map) const override;

  protected:
    ExitMovementType emt;
};

