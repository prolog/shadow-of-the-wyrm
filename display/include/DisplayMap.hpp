#pragma once
#include <boost/unordered_map.hpp>
#include "Dimensions.hpp"
#include "common.hpp"
#include "DisplayTile.hpp"

class DisplayTile;

typedef boost::unordered_map<Coordinate, DisplayTile> DisplayMapType;

// A DisplayMap is the only map the Display cares about.  It contains
// DisplayTile info, which in turn contains boiled-down Tile information.
class DisplayMap
{
  public:
    // JCD FIXME: If I keep the unordered map approach, the two-int
    // constructor can be deleted (was used only to reserve vector size).
    // Also delete rows, cols.
    DisplayMap(const int rows, const int cols);
    DisplayMap();

    // The coordinate on which to place the cursor when done - typically
    // will be whatever coordinate the player is on.
    void set_cursor_coordinate(const Coordinate& new_cursor_coordinate);
    Coordinate get_cursor_coordinate() const;

    void set(const Coordinate& key, const DisplayTile& value);
    DisplayTile at(const Coordinate& coords) const;
    Dimensions size() const;

    DisplayMapType get_tiles() const;

  protected:
    int rows, cols;
    DisplayMapType display_map;
    Coordinate cursor_coordinate;
};
