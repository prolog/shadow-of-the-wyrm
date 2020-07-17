#pragma once

#include "common.hpp"
#include "Map.hpp"

enum struct SpringsType
{
  SPRINGS_TYPE_WIDE = 0,
  SPRINGS_TYPE_TALL = 1
};

class SpringsGenerator
{
  public:
    static void generate(MapPtr map, const int start_row, const int start_col, const int springs_size, const SpringsType springs_type);
    static void generate(MapPtr map, const int start_row, const int start_col, const int springs_size, const SpringsType springs_type, const int pct_chance);

  public:
    static void generate_wide(MapPtr map, const int start_row, const int start_col, const int springs_size, const int pct_chance);
    static void generate_tall(MapPtr map, const int start_row, const int start_col, const int springs_size, const int pct_chance);
    static void add_spirit_if_necessary(MapPtr map, const int row, const int col, const int pct_chance);

    static const int PCT_CHANCE_SPIRIT;
};
