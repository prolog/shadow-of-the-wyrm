#pragma once
#include <tuple>
#include "common.hpp"
#include "Directions.hpp"
#include "Map.hpp"

// Interface for defining crypt layout strategies.  These operate on a
// given map and crypt boundary, producing the characteristic look of the
// crypt: pillars, rooms, a central vault, etc.
class ICryptLayoutStrategy
{
  public:
    virtual void create_layout(MapPtr map, const std::tuple<Coordinate, Coordinate, Coordinate>& stair_loc_and_room_boundary) = 0;
};

