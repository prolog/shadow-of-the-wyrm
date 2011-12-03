#pragma once
#include <map>
#include "Dimensions.hpp"
#include "common.hpp"
#include "DisplayTile.hpp"

class DisplayTile;


// A DisplayMap is the only map the Display cares about.  It contains
// DisplayTile info, which in turn contains boiled-down Tile information.
class DisplayMap
{
  public:
    DisplayMap();

    DisplayTile at(const Coordinate& coords) const;
    Dimensions get_dimensions() const;

  protected:
    Dimensions dimensions;
    std::map<Coordinate, DisplayTile> display_map;
};
