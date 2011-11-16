#pragma once

#include "common.hpp"
#include "Directions.hpp"
#include "Map.hpp"

class StreamGenerator
{
  public:
    static MapPtr generate(MapPtr map);

  protected:
    static MapPtr generate_stream(MapPtr map, const int start_col);

    static const int MIN_STREAM_WIDTH = 2;
    static const int MAX_STREAM_WIDTH = 3;
};
