#pragma once
#include <string>
#include <unordered_map>
#include "Dimensions.hpp"
#include "common.hpp"
#include "DisplayTile.hpp"

class DisplayTile;

using DisplayMapType = std::unordered_map<std::string, DisplayTile>;

// A DisplayMap is the only map the Display cares about.  It contains
// DisplayTile info, which in turn contains boiled-down Tile information.
// It also contains limited debug information, such as the current map
// ID.
class DisplayMap
{
  public:
    DisplayMap(const std::string& map_id, const int rows, const int cols);
    DisplayMap();

    // The coordinate on which to place the cursor when done - typically
    // will be whatever coordinate the player is on.
    void set_cursor_coordinate(const Coordinate& new_cursor_coordinate);
    Coordinate get_cursor_coordinate() const;

    void set(const Coordinate& key, const DisplayTile& value);
    DisplayTile at(const Coordinate& coords) const;
    Dimensions size() const;

    DisplayMapType get_tiles() const;
    std::string get_map_id() const;

  protected:
    std::string map_id;
    int rows, cols;
    DisplayMapType display_map;
    Coordinate cursor_coordinate;
};
