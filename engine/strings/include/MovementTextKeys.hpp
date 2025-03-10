#pragma once
#include <string>
#include "MapExit.hpp"
#include "MapTypes.hpp"

class MovementTextKeys
{
  public:
    static std::string get_cannot_exit_map_message(const MapType mt, const MapExitOutcome exit_outcome);

    static const std::string ACTION_MOVE_NO_EXIT;
    static const std::string ACTION_MOVE_NO_EXIT_COSMOS;
    static const std::string ACTION_MOVE_NO_EXIT_UP_AIR;
    static const std::string ACTION_MOVE_NO_EXIT_DOWN;
    static const std::string ACTION_MOVE_NO_EXIT_DOWN_SEA;
    static const std::string ACTION_MOVE_NO_EXIT_DOWN_SPRINGS;
    static const std::string ACTION_MOVE_ADJACENT_HOSTILE_CREATURE;
    static const std::string ACTION_MOVE_OFF_WORLD_MAP;
    static const std::string ACTION_NO_WAY_UP_WORLD_MAP;
    static const std::string ACTION_NO_WAY_UP_WORLD_MAP_NO_GODS;
    static const std::string ACTION_MOVE_OFF_OVERWORLD_MAP;
    static const std::string ACTION_MOVE_OFF_UNDERWORLD_MAP;
    static const std::string ACTION_MOVE_OFF_UNDERWATER_MAP;
    static const std::string ACTION_MOVE_OFF_COSMOS_MAP;
    static const std::string ACTION_MOVE_OFF_AIR_MAP;
    static const std::string ACTION_MOVE_OFF_BLOCKED;
    static const std::string ACTION_MOVE_DANGEROUS_FEATURE;
    static const std::string ACTION_MOVE_RACE_NOT_ALLOWED;
    static const std::string ACTION_MOVE_WRONG_STAIRS_DIRECTION;
    static const std::string ACTION_MOVE_DIVE_TOO_SHALLOW;
    static const std::string ACTION_MOVE_DIVE_ICE;
    static const std::string ITEMS_ON_TILE;
    
  protected:
    MovementTextKeys();
    ~MovementTextKeys();
};

