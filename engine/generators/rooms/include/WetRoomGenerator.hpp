#pragma once
#include "IRoomGenerator.hpp"

class WetRoomGenerator : public IRoomGenerator
{
  public:
    WetRoomGenerator();

    void generate(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col) override;

  protected:
    int pct_chance_wet;
};

