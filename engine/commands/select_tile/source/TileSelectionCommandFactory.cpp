#include <boost/make_shared.hpp>
#include "CommandKeys.hpp"
#include "Commands.hpp"
#include "Directions.hpp"
#include "TileSelectionCommands.hpp"
#include "TileSelectionCommandFactory.hpp"
#include "TileSelectionCommandKeys.hpp"

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
    command = boost::make_shared<CursorDirectionalCommand>(DIRECTION_NORTH_WEST);
  }
  else if (command_name == TileSelectionCommandKeys::CURSOR_MOVE_NORTH)
  {
    command = boost::make_shared<CursorDirectionalCommand>(DIRECTION_NORTH);
  }
  else if (command_name == TileSelectionCommandKeys::CURSOR_MOVE_NORTHEAST)
  {
    command = boost::make_shared<CursorDirectionalCommand>(DIRECTION_NORTH_EAST);
  }
  else if (command_name == TileSelectionCommandKeys::CURSOR_MOVE_WEST)
  {
    command = boost::make_shared<CursorDirectionalCommand>(DIRECTION_WEST);
  }
  else if (command_name == TileSelectionCommandKeys::CURSOR_MOVE_EAST)
  {
    command = boost::make_shared<CursorDirectionalCommand>(DIRECTION_EAST);
  }
  else if (command_name == TileSelectionCommandKeys::CURSOR_MOVE_SOUTHWEST)
  {
    command = boost::make_shared<CursorDirectionalCommand>(DIRECTION_SOUTH_WEST);
  }
  else if (command_name == TileSelectionCommandKeys::CURSOR_MOVE_SOUTH)
  {
    command = boost::make_shared<CursorDirectionalCommand>(DIRECTION_SOUTH);
  }
  else if (command_name == TileSelectionCommandKeys::CURSOR_MOVE_SOUTHEAST)
  {
    command = boost::make_shared<CursorDirectionalCommand>(DIRECTION_SOUTH_EAST);
  }
  else if (command_name == TileSelectionCommandKeys::CANCEL_TILE_SELECTION)
  {
    command = boost::make_shared<CancelTileSelectionCommand>();
  }
  else if (command_name == TileSelectionCommandKeys::TARGET_TILE)
  {
    command = boost::make_shared<TargetTileCommand>();
  }
  else if (command_name == CommandKeys::BESTIARY)
  {
    command = boost::make_shared<BestiaryCommand>();
  }
  
  return command;
}

CommandFactory* TileSelectionCommandFactory::clone()
{
  return new TileSelectionCommandFactory(*this);
}


CommandFactoryType TileSelectionCommandFactory::get_factory_type() const
{
  return COMMAND_FACTORY_TYPE_SELECT_TILE;
}

ClassIdentifier TileSelectionCommandFactory::internal_class_identifier() const
{
  return CLASS_ID_TILE_SELECTION_COMMAND_FACTORY;
}

#ifdef UNIT_TESTS
#include "unit_tests/TileSelectionCommandFactory_test.cpp"
#endif
