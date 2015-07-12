#pragma once
#include "IRoomGenerator.hpp"

class BasicRoomGenerator : public IRoomGenerator
{
  public:
    void generate(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col) override;
};

