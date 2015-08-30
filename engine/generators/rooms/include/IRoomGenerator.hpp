#pragma once
#include <memory>
#include "Map.hpp"

class IRoomGenerator
{
  public:
    virtual void generate(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col) = 0;
};

using IRoomGeneratorPtr = std::shared_ptr<IRoomGenerator>;

