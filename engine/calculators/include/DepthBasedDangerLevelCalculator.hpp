#pragma once
#include "IDangerLevelCalculator.hpp"

class DepthBasedDangerLevelCalculator : public IDangerLevelCalculator
{
  public:
    DepthBasedDangerLevelCalculator(const ExitMovementType new_emt);
    virtual int calculate(MapPtr old_map, MapPtr new_map) const override;

  protected:
    bool is_more_dangerous(const int delta, const int current_depth) const;

    ExitMovementType emt;
};

