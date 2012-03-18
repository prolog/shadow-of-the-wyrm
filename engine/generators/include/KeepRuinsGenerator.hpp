#pragma once
#include "Generator.hpp"
#include "Map.hpp"

class KeepRuinsGenerator : public Generator
{
 public:
    KeepRuinsGenerator(MapPtr new_base_map);

    MapPtr generate(const Dimensions& dim);
    MapPtr generate();

  protected:
    void create_keep(MapPtr map, const int start_row, const int start_col, const int height, const int width);
    void populate_keep(MapPtr map, const int start_row, const int start_col, const int height, const int width);
    void create_entrance(MapPtr map, const int start_row, const int start_col, const int height, const int width);
    
    MapPtr base_map;
};
