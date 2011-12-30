#include "CommandFactory.hpp"
#include "CommandKeys.hpp"
#include "Commands.hpp"

using namespace std;

CommandFactory::CommandFactory()
{
}

CommandFactory::~CommandFactory()
{
}

CommandPtr CommandFactory::create(const string& command_name)
{
  CommandPtr command;

  if (command_name == CommandKeys::QUIT)
  {
    command = CommandPtr(new QuitCommand());
  }
  else if (command_name == CommandKeys::VERSION)
  {
    command = CommandPtr(new VersionCommand());
  }
  else if (command_name == CommandKeys::MOVE_NORTHEAST)
  {
    command = CommandPtr(new MovementCommand(DIRECTION_NORTH_EAST));
  }
  else if (command_name == CommandKeys::MOVE_NORTH)
  {
    command = CommandPtr(new MovementCommand(DIRECTION_NORTH));
  }
  else if (command_name == CommandKeys::MOVE_NORTHWEST)
  {
    command = CommandPtr(new MovementCommand(DIRECTION_NORTH_WEST));
  }
  else if (command_name == CommandKeys::MOVE_EAST)
  {
    command = CommandPtr(new MovementCommand(DIRECTION_EAST));
  }
  else if (command_name == CommandKeys::SEARCH)
  {
    command = CommandPtr(new SearchCommand());
  }
  else if (command_name == CommandKeys::MOVE_WEST)
  {
    command = CommandPtr(new MovementCommand(DIRECTION_WEST));
  }
  else if (command_name == CommandKeys::MOVE_SOUTHEAST)
  {
    command = CommandPtr(new MovementCommand(DIRECTION_SOUTH_EAST));
  }
  else if (command_name == CommandKeys::MOVE_SOUTH)
  {
    command = CommandPtr(new MovementCommand(DIRECTION_SOUTH));
  }
  else if (command_name == CommandKeys::MOVE_SOUTHWEST)
  {
    command = CommandPtr(new MovementCommand(DIRECTION_SOUTH_WEST));
  }

  return command;
}
