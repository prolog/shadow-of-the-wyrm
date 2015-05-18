#pragma once
#include "Directions.hpp"

class DirectionUtils
{
  public:
    static bool is_cardinal(const Direction d);
    static bool is_ordinal(const Direction d);
    static CardinalDirection get_opposite_direction(const CardinalDirection cd);
    static Direction get_opposite_direction(const Direction d);

  protected:
    DirectionUtils();
};
