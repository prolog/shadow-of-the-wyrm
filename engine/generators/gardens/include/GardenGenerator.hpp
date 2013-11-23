#pragma once
#include <memory>
#include "Map.hpp"

// Generates a garden on top of a given map, over the given row/col.
// Think of GardenGenerators as more of a decorator than a pure
// generator.
//
// Abstract base class.
class GardenGenerator
{
  public:
    GardenGenerator(MapPtr map, const int map_window_start_row, const int map_window_start_col, const int map_window_height, const int map_window_width);

    virtual void generate() = 0;

  protected:
    MapPtr map;
    int window_start_row;
    int window_start_col;
    int window_height;
    int window_width;
    int window_end_row_inc; // end row inclusive - use <=
    int window_end_col_inc; // end col inclusive - use <=
};

typedef std::shared_ptr<GardenGenerator> GardenGeneratorPtr;

