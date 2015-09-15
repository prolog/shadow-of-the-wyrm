#pragma once
#include "Map.hpp"

class MapCursor
{
  public:
    void set_cursor_location(MapPtr current_map, const Coordinate& c);
    void update_cursor_location(MapPtr current_map, const Direction d);
    void reset_cursor(MapPtr current_map);

    // bool is whether or not to override the default cursor display
    // settings.  We want to always show the cursor when selecting tiles
    // for looking, magic, etc., but not when the cursor is just
    // centred on the player.
    std::pair<Coordinate, bool> get_cursor_location(MapPtr current_map) const;

  protected:
    static const std::string MAP_CURSOR_LOCATION;
};
