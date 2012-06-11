#pragma once
#include <vector>
#include "common.hpp"

class BresenhamLine
{
  public:
    std::vector<Coordinate> get_points_in_line(int y1, int x1, int y2, int x2);
};
