#pragma once
#include "IRoomGenerator.hpp"

// sorry for the bad pun
class MushRoomGenerator : public IRoomGenerator
{
  public:
    MushRoomGenerator(const bool new_skip_tile_generation);

    void generate(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col) override;
    virtual ~MushRoomGenerator() = default;

  protected:
    bool skip_tile_generation;

    static const int PCT_CHANCE_MUSHROOMS;
    static const int PCT_CHANCE_SPECIAL_MUSHROOM;
};

