#pragma once
#include <string>

class TileSelectionCommandKeys
{
  public:
    static const std::string CURSOR_MOVE_NORTHWEST;
    static const std::string CURSOR_MOVE_NORTH;
    static const std::string CURSOR_MOVE_NORTHEAST;
    static const std::string CURSOR_MOVE_WEST;
    static const std::string CURSOR_MOVE_EAST;
    static const std::string CURSOR_MOVE_SOUTHWEST;
    static const std::string CURSOR_MOVE_SOUTH;
    static const std::string CURSOR_MOVE_SOUTHEAST;
    static const std::string CANCEL_TILE_SELECTION;

  protected:
    TileSelectionCommandKeys();
    ~TileSelectionCommandKeys();
};
