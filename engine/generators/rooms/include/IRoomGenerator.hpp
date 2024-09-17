#pragma once
#include <memory>
#include "Map.hpp"

class IRoomGenerator
{
  public:
    virtual void generate(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col) = 0;
    virtual ~IRoomGenerator() = default;
};

using IRoomGeneratorPtr = std::unique_ptr<IRoomGenerator>;

