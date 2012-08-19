#include <boost/make_shared.hpp>
#include "Directions.hpp"
#include "TileSelectionCommands.hpp"
#include "TileSelectionCommandFactory.hpp"
#include "TileSelectionCommandKeys.hpp"

using boost::make_shared;

TileSelectionCommandFactory::TileSelectionCommandFactory()
{
}

TileSelectionCommandFactory::~TileSelectionCommandFactory()
{
}

CommandPtr TileSelectionCommandFactory::create(const int key, const std::string& command_name)
{
  CommandPtr command;
  
  if (command_name == TileSelectionCommandKeys::CURSOR_MOVE_NORTHWEST)
  {
    command = make_shared<CursorDirectionalCommand>(DIRECTION_NORTH_WEST);
  }
  else if (command_name == TileSelectionCommandKeys::CURSOR_MOVE_NORTH)
  {
    command = make_shared<CursorDirectionalCommand>(DIRECTION_NORTH);
  }
  else if (command_name == TileSelectionCommandKeys::CURSOR_MOVE_NORTHEAST)
  {
    command = make_shared<CursorDirectionalCommand>(DIRECTION_NORTH_EAST);
  }
  else if (command_name == TileSelectionCommandKeys::CURSOR_MOVE_WEST)
  {
    command = make_shared<CursorDirectionalCommand>(DIRECTION_WEST);
  }
  else if (command_name == TileSelectionCommandKeys::CURSOR_MOVE_EAST)
  {
    command = make_shared<CursorDirectionalCommand>(DIRECTION_EAST);
  }
  else if (command_name == TileSelectionCommandKeys::CURSOR_MOVE_SOUTHWEST)
  {
    command = make_shared<CursorDirectionalCommand>(DIRECTION_SOUTH_WEST);
  }
  else if (command_name == TileSelectionCommandKeys::CURSOR_MOVE_SOUTH)
  {
    command = make_shared<CursorDirectionalCommand>(DIRECTION_SOUTH);
  }
  else if (command_name == TileSelectionCommandKeys::CURSOR_MOVE_SOUTHEAST)
  {
    command = make_shared<CursorDirectionalCommand>(DIRECTION_SOUTH_EAST);
  }
  else if (command_name == TileSelectionCommandKeys::CANCEL_TILE_SELECTION)
  {
    command = make_shared<CancelTileSelectionCommand>();
  }
  else if (command_name == TileSelectionCommandKeys::TARGET_TILE)
  {
    command = make_shared<TargetTileCommand>();
  }
  
  return command;
}


CommandFactoryType TileSelectionCommandFactory::get_factory_type() const
{
  return COMMAND_FACTORY_TYPE_SELECT_TILE;
}
