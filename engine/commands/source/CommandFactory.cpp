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

CommandPtr CommandFactory::create(const int key, const string& command_name)
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
  else if (command_name == CommandKeys::GAME_DATE_TIME)
  {
    command = CommandPtr(new GameDateTimeCommand());
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
  else if (command_name == CommandKeys::MOVE_UP)
  {
    command = CommandPtr(new MoveUpLevelCommand());
  }
  else if (command_name == CommandKeys::MOVE_DOWN)
  {
    command = CommandPtr(new MoveDownLevelCommand());
  }
  else if (command_name == CommandKeys::PICK_UP_ITEM)
  {
    command = CommandPtr(new PickUpCommand());
  }
  else if (command_name == CommandKeys::DROP_ITEM)
  {
    command = CommandPtr(new DropCommand());
  }
  else if (command_name == CommandKeys::CHAR_DUMP)
  {
    command = CommandPtr(new CharDumpCommand());
  }
  else if (command_name == CommandKeys::INVENTORY)
  {
    command = CommandPtr(new InventoryCommand());
  }

  return command;
}

CommandFactoryType CommandFactory::get_factory_type() const
{
  return COMMAND_FACTORY_TYPE_MAP;
}
