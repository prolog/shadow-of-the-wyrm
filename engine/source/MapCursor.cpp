#include "MapCursor.hpp"
#include "MapUtils.hpp"

using std::string;

const string MapCursor::MAP_CURSOR_LOCATION = "map cursor";

// Overwrite the current map cursor location
void MapCursor::set_cursor_location(MapPtr current_map, const Coordinate& c)
{
  current_map->add_or_update_location(MAP_CURSOR_LOCATION, c);
}

void MapCursor::update_cursor_location(MapPtr current_map, const Direction direction)
{
  Coordinate current_coords = get_cursor_location(current_map);
  
  if (MapUtils::is_valid_move(current_map->size(), current_coords, direction))
  {
    Coordinate new_coords = MapUtils::get_new_coordinate(current_coords, direction);
    set_cursor_location(current_map, new_coords);
  }
}

void MapCursor::reset_cursor(MapPtr current_map)
{
  current_map->remove_location(MAP_CURSOR_LOCATION);
}

Coordinate MapCursor::get_cursor_location(MapPtr current_map) const
{
  // Get the cursor location.
  // If the cursor actually exists in the map, use that.
  // Otherwise, use the player for the cursor.
  Coordinate c;
  
  if (current_map->has_location(MAP_CURSOR_LOCATION))
  {
    c = current_map->get_location(MAP_CURSOR_LOCATION);
  }
  else
  {
    c = current_map->get_location(WorldMapLocationTextKeys::CURRENT_PLAYER_LOCATION);
  }
  
  return c;
}
