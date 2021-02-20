#pragma once
#include "Map.hpp"

class FollowerCalculator
{
  public:
    std::pair<int, int> calculate_x_in_y_chance_adventurer(const Depth& depth) const;
    std::pair<int, int> calculate_x_in_y_chance_hireling(const Depth& depth) const;

  protected:
    static const int BASE_X_ADVENTURER;
    static const int BASE_Y_ADVENTURER;
    static const int BASE_X_HIRELING;
    static const int BASE_Y_HIRELING;
};

