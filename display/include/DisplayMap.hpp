#pragma once
#include <boost/unordered_map.hpp>
#include "Dimensions.hpp"
#include "common.hpp"
#include "DisplayTile.hpp"

class DisplayTile;

// A DisplayMap is the only map the Display cares about.  It contains
// DisplayTile info, which in turn contains boiled-down Tile information.
class DisplayMap
{
  public:
    DisplayMap(const int rows, const int cols);

    // The coordinate on which to place the cursor when done - typically
    // will be whatever coordinate the player is on.
    void set_cursor_coordinate(const Coordinate& new_cursor_coordinate);
    Coordinate get_cursor_coordinate() const;

    void set(const Coordinate& key, const DisplayTile& value);
    DisplayTile at(const Coordinate& coords) const;
    Dimensions size() const;

  protected:
    std::string get_key(const Coordinate& c) const;

    int rows, cols;
    boost::unordered_map<std::string, DisplayTile> display_map;
    Coordinate cursor_coordinate;
};
