#pragma once

#include "common.hpp"
#include "Directions.hpp"
#include "Map.hpp"

class StreamGenerator
{
  public:
    static void generate(MapPtr map);

  protected:
    static void generate_stream(MapPtr map, const int start_col);

    static const int MIN_STREAM_WIDTH = 2;
    static const int MAX_STREAM_WIDTH = 3;
};
