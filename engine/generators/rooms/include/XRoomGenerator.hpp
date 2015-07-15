#pragma once
#include "IRoomGenerator.hpp"

// Create a room with an "X" in it, joined to the east-west walls,
// made out of rock.
class XRoomGenerator : public IRoomGenerator
{
  public:
    void generate(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col) override;

  protected:
    void generate_x(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col);
};

