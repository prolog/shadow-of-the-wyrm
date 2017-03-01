#pragma once
#include <utility>
#include "common.hpp"

class Building
{
  public:
    Building(const Coordinate& top_left, const Coordinate& bottom_right, const Coordinate& door);

    // Get the top-left/bottom-right coordinates for the entire building.
    std::pair<Coordinate, Coordinate> get_coords() const;

    // Get the top-left/bottom-right coordinates for the interior.
    std::pair<Coordinate, Coordinate> get_interior_coords() const;

    Coordinate get_door_coord() const;

  protected:
    Coordinate start_c;
    Coordinate end_c;
    Coordinate door_c;
};

