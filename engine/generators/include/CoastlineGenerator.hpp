#pragma once
#include "Map.hpp"

// Generates coastline around a particular map.  The assumption is that this
// isn't the world map, but rather an overworld map.
class CoastlineGenerator
{
  public:
    CoastlineGenerator();

    void generate(MapPtr map, const bool north, const bool south, const bool east, const bool west);
  
  protected:
    void generate_north(MapPtr map);
    void generate_south(MapPtr map);
    void generate_east(MapPtr map);
    void generate_west(MapPtr map);

    int get_random_chance_shoals() const;

    int jiggle(const int y_val, const int min, const int max) const;
    void fill_sea(MapPtr map, const int y_start, const int y_end, const int x_start, const int x_end);

    int chance_shoals_y;
    static const int PCT_CHANCE_SHIFT_DIR;
    static const int MAX_COAST_OFFSET;
};
