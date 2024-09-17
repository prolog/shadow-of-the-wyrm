#pragma once
#include "IRoomGenerator.hpp"

class CaveInRoomGenerator : public IRoomGenerator
{
  public:
    CaveInRoomGenerator();
    virtual ~CaveInRoomGenerator() = default;

    void generate(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col) override;

  protected:
    int pct_chance_cave_in;
};

