#pragma once
#include "DangerLevelCalculator.hpp"

class DepthBasedDangerLevelCalculator : public DangerLevelCalculator
{
  public:
    DepthBasedDangerLevelCalculator(const ExitMovementType new_emt);
    virtual ~DepthBasedDangerLevelCalculator() = default;

    virtual int calculate(MapPtr old_map, MapPtr new_map) const override;

  protected:
    bool is_more_dangerous(const int delta, const int current_depth) const;
    int calculate_delta(const Depth& map_depth, const Depth& new_map_depth) const;

    ExitMovementType emt;
};

