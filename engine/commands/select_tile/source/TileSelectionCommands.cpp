#include "Conversion.hpp"
#include "TileSelectionCommands.hpp"

using std::string;

CursorDirectionalCommand::CursorDirectionalCommand(const Direction d)
: Command(""), direction(d)
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
CancelTileSelectionCommand::CancelTileSelectionCommand()
: Command(TileSelectionCommandKeys::CANCEL_TILE_SELECTION)
{
}

CancelTileSelectionCommand::~CancelTileSelectionCommand()
{
}
