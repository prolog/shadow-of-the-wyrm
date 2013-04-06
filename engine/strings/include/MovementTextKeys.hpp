#pragma once
#include <string>

class MovementTextKeys
{
  public:
    static const std::string ACTION_MOVE_NO_EXIT;
    static const std::string ACTION_MOVE_ADJACENT_HOSTILE_CREATURE;
    static const std::string ACTION_MOVE_OFF_WORLD_MAP;
    static const std::string ACTION_NO_WAY_UP_WORLD_MAP;
    static const std::string ACTION_MOVE_OFF_OVERWORLD_MAP;
    static const std::string ACTION_MOVE_OFF_UNDERWORLD_MAP;
    static const std::string ITEMS_ON_TILE;
    
  protected:
    MovementTextKeys();
    ~MovementTextKeys();
};

