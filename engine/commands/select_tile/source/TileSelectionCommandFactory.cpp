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
    command = std::make_shared<CursorDirectionalCommand>(DIRECTION_NORTH_WEST, key);
  }
  else if (command_name == TileSelectionCommandKeys::CURSOR_MOVE_NORTH)
  {
    command = std::make_shared<CursorDirectionalCommand>(DIRECTION_NORTH, key);
  }
  else if (command_name == TileSelectionCommandKeys::CURSOR_MOVE_NORTHEAST)
  {
    command = std::make_shared<CursorDirectionalCommand>(DIRECTION_NORTH_EAST, key);
  }
  else if (command_name == TileSelectionCommandKeys::CURSOR_MOVE_WEST)
  {
    command = std::make_shared<CursorDirectionalCommand>(DIRECTION_WEST, key);
  }
  else if (command_name == TileSelectionCommandKeys::CURSOR_MOVE_EAST)
  {
    command = std::make_shared<CursorDirectionalCommand>(DIRECTION_EAST, key);
  }
  else if (command_name == TileSelectionCommandKeys::CURSOR_MOVE_SOUTHWEST)
  {
    command = std::make_shared<CursorDirectionalCommand>(DIRECTION_SOUTH_WEST, key);
  }
  else if (command_name == TileSelectionCommandKeys::CURSOR_MOVE_SOUTH)
  {
    command = std::make_shared<CursorDirectionalCommand>(DIRECTION_SOUTH, key);
  }
  else if (command_name == TileSelectionCommandKeys::CURSOR_MOVE_SOUTHEAST)
  {
    command = std::make_shared<CursorDirectionalCommand>(DIRECTION_SOUTH_EAST, key);
  }
  else if (command_name == TileSelectionCommandKeys::CANCEL_TILE_SELECTION)
  {
    command = std::make_shared<CancelTileSelectionCommand>(key);
  }
  else if (command_name == TileSelectionCommandKeys::TARGET_TILE)
  {
    command = std::make_shared<TargetTileCommand>(key);
  }
  else if (command_name == TileSelectionCommandKeys::TARGET_NEXT_CREATURE)
  {
    command = std::make_shared<TargetNextCreatureCommand>(key);
  }
  else if (command_name == TileSelectionCommandKeys::TARGET_PREV_CREATURE)
  {
    command = std::make_shared<TargetPrevCreatureCommand>(key);
  }
  else if (command_name == CommandKeys::BESTIARY)
  {
    command = std::make_shared<BestiaryCommand>(key);
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
