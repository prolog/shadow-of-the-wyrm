#pragma once
#include <set>
#include <vector>
#include "Dimensions.hpp"
#include "Directions.hpp"

class DirectionUtils
{
  public:
    static bool is_cardinal(const Direction d);
    static std::vector<CardinalDirection> get_perpendicular_directions(const CardinalDirection cd);
    static bool is_ordinal(const Direction d);
    static Direction to_direction(const CardinalDirection cd);
    static CardinalDirection to_cardinal_direction(const Direction d);
    static CardinalDirection to_cardinal_direction(const Direction d, const Dimensions& dim, const Coordinate& c);
    static CardinalDirection get_opposite_direction(const CardinalDirection cd);
    static Direction get_opposite_direction(const Direction d);
    static bool direction_matches_category(const Direction d, const DirectionCategory dc);
    static std::set<Direction> get_all_directions_for_category(const DirectionCategory dc);

  protected:
    DirectionUtils();
};
