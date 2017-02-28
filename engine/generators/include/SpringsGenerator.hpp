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
    static MapPtr generate(MapPtr map, const int start_row, const int start_col, const int springs_size, const SpringsType springs_type);

  public:
    static MapPtr generate_wide(MapPtr map, const int start_row, const int start_col, const int springs_size);
    static MapPtr generate_tall(MapPtr map, const int start_row, const int start_col, const int springs_size);
    static void add_fairy_spirit_if_necessary(MapPtr map, const int row, const int col);

    static const int PCT_CHANCE_FAIRY_SPIRIT;
};
