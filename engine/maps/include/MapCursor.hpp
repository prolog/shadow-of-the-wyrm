#pragma once
#include "Map.hpp"

class MapCursor
{
  public:
    void set_cursor_location(MapPtr current_map, const Coordinate& c);
    void update_cursor_location(MapPtr current_map, const Direction d);
    void reset_cursor(MapPtr current_map);
    Coordinate get_cursor_location(MapPtr current_map) const;

  protected:
    static const std::string MAP_CURSOR_LOCATION;
};
