#pragma once
#include "Map.hpp"

class KeepRuinsGenerator
{
 public:
    static MapPtr generate(MapPtr map);

  protected:
    static void create_keep(MapPtr map, const int start_row, const int start_col, const int height, const int width);
    static void populate_keep(MapPtr map, const int start_row, const int start_col, const int height, const int width);
    static void create_entrance(MapPtr map, const int start_row, const int start_col, const int height, const int width);
};
