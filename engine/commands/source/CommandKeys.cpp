#include "CommandKeys.hpp"

using namespace std;

CommandKeys::CommandKeys()
{
}

CommandKeys::~CommandKeys()
{
}

// Initialize the command keys
string CommandKeys::QUIT           = "QUIT";
string CommandKeys::VERSION        = "VERSION";
string CommandKeys::MOVE_NORTHWEST = "MOVE_NORTHWEST";
string CommandKeys::MOVE_NORTH     = "MOVE_NORTH";
string CommandKeys::MOVE_NORTHEAST = "MOVE_NORTHEAST";
string CommandKeys::MOVE_WEST      = "MOVE_WEST";
string CommandKeys::SEARCH         = "SEARCH";
string CommandKeys::MOVE_EAST      = "MOVE_EAST";
string CommandKeys::MOVE_SOUTHWEST = "MOVE_SOUTHWEST";
string CommandKeys::MOVE_SOUTH     = "MOVE_SOUTH";
string CommandKeys::MOVE_SOUTHEAST = "MOVE_SOUTHEAST";
string CommandKeys::MOVE_UP        = "MOVE_UP";
string CommandKeys::MOVE_DOWN      = "MOVE_DOWN";

bool CommandKeys::is_movement_type_key(const string& key)
{
  bool is_movement = false;

  if ((key == CommandKeys::MOVE_NORTHWEST)
   || (key == CommandKeys::MOVE_NORTH)
   || (key == CommandKeys::MOVE_NORTHEAST)
   || (key == CommandKeys::MOVE_WEST)
   || (key == CommandKeys::MOVE_EAST)
   || (key == CommandKeys::MOVE_SOUTHWEST)
   || (key == CommandKeys::MOVE_SOUTH)
   || (key == CommandKeys::MOVE_SOUTHEAST))
  {
    is_movement = true;
  }

  return is_movement;
}
