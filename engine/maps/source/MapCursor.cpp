#include "CoordUtils.hpp"
#include "MapCursor.hpp"
#include "WorldMapLocationTextKeys.hpp"

using namespace std;

const string MapCursor::MAP_CURSOR_LOCATION = "map cursor";

// Overwrite the current map cursor location
void MapCursor::set_cursor_location(MapPtr current_map, const Coordinate& c)
{
  current_map->add_or_update_location(MAP_CURSOR_LOCATION, c);
}

void MapCursor::update_cursor_location(MapPtr current_map, const Direction direction)
{
  pair<Coordinate, bool> current_coords = get_cursor_location(current_map);
  
  if (CoordUtils::is_valid_move(current_map->size(), current_coords.first, direction))
  {
    Coordinate new_coords = CoordUtils::get_new_coordinate(current_coords.first, direction);
    set_cursor_location(current_map, new_coords);
  }
}

void MapCursor::reset_cursor(MapPtr current_map)
{
  current_map->remove_location(MAP_CURSOR_LOCATION);
}

pair<Coordinate, bool> MapCursor::get_cursor_location(MapPtr current_map) const
{
  // Get the cursor location.
  // If the cursor actually exists in the map, use that.
  // Otherwise, use the player for the cursor.
  pair<Coordinate, bool> c;
  
  if (current_map->has_location(MAP_CURSOR_LOCATION))
  {
    c = make_pair(current_map->get_location(MAP_CURSOR_LOCATION), true);
  }
  else
  {
    c = make_pair(current_map->get_location(WorldMapLocationTextKeys::CURRENT_PLAYER_LOCATION), false);
  }
  
  return c;
}
