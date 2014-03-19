#include "Conversion.hpp"
#include "TileSelectionCommands.hpp"

using std::string;

CursorDirectionalCommand::CursorDirectionalCommand(const Direction d, const int key)
: Command("", key), direction(d)
{
  string name = DirectionEnum::to_string(direction);
  command_name = name;
}

CursorDirectionalCommand::~CursorDirectionalCommand()
{
}

Direction CursorDirectionalCommand::get_direction() const
{
  return direction;
}

// Cancel tile selection
CancelTileSelectionCommand::CancelTileSelectionCommand(const int key)
: Command(TileSelectionCommandKeys::CANCEL_TILE_SELECTION, key)
{
}

CancelTileSelectionCommand::~CancelTileSelectionCommand()
{
}

// Target a particular tile
TargetTileCommand::TargetTileCommand(const int key)
: Command(TileSelectionCommandKeys::TARGET_TILE, key)
{
}

TargetTileCommand::~TargetTileCommand()
{
}

// Target the next creature in the list
TargetNextCreatureCommand::TargetNextCreatureCommand(int key)
: Command(TileSelectionCommandKeys::TARGET_NEXT_CREATURE, key)
{
}

TargetNextCreatureCommand::~TargetNextCreatureCommand()
{
}

// Target the previous creature in the list
TargetPrevCreatureCommand::TargetPrevCreatureCommand(int key)
: Command(TileSelectionCommandKeys::TARGET_PREV_CREATURE, key)
{
}

TargetPrevCreatureCommand::~TargetPrevCreatureCommand()
{
}