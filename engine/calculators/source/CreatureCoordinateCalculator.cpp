#include "CreatureCoordinateCalculator.hpp"

Coordinate CreatureCoordinateCalculator::calculate_engine_coordinate(const MapDisplayArea& display_area, MapPtr current_map, const Coordinate& reference_coords)
{
  uint display_width = display_area.get_width();
  uint display_height = display_area.get_height();
  int cursor_row = reference_coords.first;
  int cursor_col = reference_coords.second;

  Dimensions d = current_map->size();
  int map_height = d.get_y();
  int map_width  = d.get_x();
  int engine_map_start_row = std::min(map_height - display_height, ((int)(cursor_row / display_height)) * display_height);
  int engine_map_start_col = std::min(map_width - display_width, ((int)(cursor_col / display_width)) * display_width);

  Coordinate engine_coord(engine_map_start_row, engine_map_start_col);
  return engine_coord;
}

Coordinate CreatureCoordinateCalculator::calculate_display_coordinate(const MapDisplayArea& display_area, MapPtr current_map, const Coordinate& reference_coords)
{
  uint display_width = display_area.get_width();
  uint display_height = display_area.get_height();
  int cursor_row = reference_coords.first;
  int cursor_col = reference_coords.second;

  Dimensions d = current_map->size();
  int map_height = d.get_y();
  int map_width  = d.get_x();
  Coordinate engine_coord = calculate_engine_coordinate(display_area, current_map, reference_coords);
  
  // Ignore the decimal part - we only care about the int part.
  int engine_map_start_row = std::min(map_height - display_height, ((int)(cursor_row / display_height)) * display_height);
  int engine_map_start_col = std::min(map_width - display_width, ((int)(cursor_col / display_width)) * display_width);
  
  uint start_y = std::max<int>(0, reference_coords.first - engine_map_start_row);
  uint start_x = std::max<int>(0, reference_coords.second - engine_map_start_col);

  Coordinate display_coord(start_y, start_x);
  return display_coord;
}
