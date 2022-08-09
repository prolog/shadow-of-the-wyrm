#include "MovementTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

// Text keys for text related to movement in some way.
MovementTextKeys::MovementTextKeys()
{
}

MovementTextKeys::~MovementTextKeys()
{
}

string MovementTextKeys::get_cannot_exit_map_message(const MapType mt, const MapExitOutcome exit_outcome)
{
  static_assert(MapType::MAP_TYPE_LAST_INC == MapType(5), "Unrecognized MapType::MAP_TYPE_LAST_INC");

  string msg = ACTION_MOVE_OFF_BLOCKED;

  if (exit_outcome == MapExitOutcome::EXIT_BLOCKED)
  {
    return StringTable::get(msg);
  }
  else
  {
    if (mt == MapType::MAP_TYPE_UNDERWATER)
    {
      msg = ACTION_MOVE_OFF_UNDERWATER_MAP;
    }
    else if (mt == MapType::MAP_TYPE_UNDERWORLD)
    {
      msg = ACTION_MOVE_OFF_UNDERWORLD_MAP;
    }
    else if (mt == MapType::MAP_TYPE_WORLD)
    {
      msg = ACTION_MOVE_OFF_WORLD_MAP;
    }
    else if (mt == MapType::MAP_TYPE_COSMOS)
    {
      msg = ACTION_MOVE_OFF_COSMOS_MAP;
    }
    else if (mt == MapType::MAP_TYPE_AIR)
    {
      msg = ACTION_MOVE_OFF_AIR_MAP;
    }

    msg = StringTable::get(msg);
    return msg;
  }
}


const string MovementTextKeys::ACTION_MOVE_NO_EXIT               = "ACTION_MOVE_NO_EXIT";
const string MovementTextKeys::ACTION_MOVE_NO_EXIT_COSMOS        = "ACTION_MOVE_NO_EXIT_COSMOS";
const string MovementTextKeys::ACTION_MOVE_NO_EXIT_UP_AIR        = "ACTION_MOVE_NO_EXIT_UP_AIR";
const string MovementTextKeys::ACTION_MOVE_NO_EXIT_DOWN          = "ACTION_MOVE_NO_EXIT_DOWN";
const string MovementTextKeys::ACTION_MOVE_NO_EXIT_DOWN_SEA      = "ACTION_MOVE_NO_EXIT_DOWN_SEA";
const string MovementTextKeys::ACTION_MOVE_NO_EXIT_DOWN_SPRINGS  = "ACTION_MOVE_NO_EXIT_DOWN_SPRINGS";
const string MovementTextKeys::ACTION_MOVE_ADJACENT_HOSTILE_CREATURE = "ACTION_MOVE_ADJACENT_HOSTILE_CREATURE";
const string MovementTextKeys::ACTION_MOVE_OFF_WORLD_MAP         = "ACTION_MOVE_OFF_WORLD_MAP";
const string MovementTextKeys::ACTION_NO_WAY_UP_WORLD_MAP        = "ACTION_NO_WAY_UP_WORLD_MAP";
const string MovementTextKeys::ACTION_MOVE_OFF_OVERWORLD_MAP     = "ACTION_MOVE_OFF_OVERWORLD_MAP";
const string MovementTextKeys::ACTION_MOVE_OFF_UNDERWORLD_MAP    = "ACTION_MOVE_OFF_UNDERWORLD_MAP";
const string MovementTextKeys::ACTION_MOVE_OFF_UNDERWATER_MAP    = "ACTION_MOVE_OFF_UNDERWATER_MAP";
const string MovementTextKeys::ACTION_MOVE_OFF_COSMOS_MAP        = "ACTION_MOVE_OFF_COSMOS_MAP";
const string MovementTextKeys::ACTION_MOVE_OFF_AIR_MAP           = "ACTION_MOVE_OFF_AIR_MAP";
const string MovementTextKeys::ACTION_MOVE_OFF_BLOCKED           = "ACTION_MOVE_OFF_BLOCKED";
const string MovementTextKeys::ACTION_MOVE_DANGEROUS_FEATURE     = "ACTION_MOVE_DANGEROUS_FEATURE";
const string MovementTextKeys::ACTION_MOVE_RACE_NOT_ALLOWED      = "ACTION_MOVE_RACE_NOT_ALLOWED";
const string MovementTextKeys::ITEMS_ON_TILE                     = "ITEMS_ON_TILE";
