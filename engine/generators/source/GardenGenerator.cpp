#include "GardenGenerator.hpp"

GardenGenerator::GardenGenerator(MapPtr new_map, const int map_window_start_row, const int map_window_start_col, const int map_window_height, const int map_window_width)
: map(new_map), window_start_row(map_window_start_row),
window_start_col(map_window_start_col), window_height(map_window_height),
window_width(map_window_width), window_end_row_inc(window_start_row + window_height), window_end_col_inc(window_start_col + window_width)
{
}

// ::generate() is defined in implementing classes.
