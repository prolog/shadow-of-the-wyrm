#pragma once
#include "IRoomGenerator.hpp"

// sorry for the bad pun
class MushRoomGenerator : public IRoomGenerator
{
  public:
    void generate(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col) override;

  protected:
    static const int PCT_CHANCE_MUSHROOMS;
    static const int PCT_CHANCE_SPECIAL_MUSHROOM;
};

