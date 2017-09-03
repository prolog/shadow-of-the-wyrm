#pragma once
#include <string>
#include "MapTypes.hpp"

class MovementTextKeys
{
  public:
    static std::string get_cannot_exit_map_message(const MapType mt);

    static const std::string ACTION_MOVE_NO_EXIT;
    static const std::string ACTION_MOVE_ADJACENT_HOSTILE_CREATURE;
    static const std::string ACTION_MOVE_OFF_WORLD_MAP;
    static const std::string ACTION_NO_WAY_UP_WORLD_MAP;
    static const std::string ACTION_MOVE_OFF_OVERWORLD_MAP;
    static const std::string ACTION_MOVE_OFF_UNDERWORLD_MAP;
    static const std::string ACTION_MOVE_OFF_UNDERWATER_MAP;
    static const std::string ACTION_MOVE_OFF_COSMOS_MAP;
    static const std::string ACTION_MOVE_DANGEROUS_FEATURE;
    static const std::string ITEMS_ON_TILE;
    
  protected:
    MovementTextKeys();
    ~MovementTextKeys();
};

