#include "Commands.hpp"
#include "CommandKeys.hpp"
#include "Conversion.hpp"

using namespace std;

// Quit
QuitCommand::QuitCommand()
: Command(CommandKeys::QUIT)
{
}

QuitCommand::~QuitCommand()
{
}

// Version
VersionCommand::VersionCommand()
: Command(CommandKeys::VERSION)
{
}

VersionCommand::~VersionCommand()
{
}

// Directional
DirectionalCommand::DirectionalCommand(const Direction d)
: Command("") // This will be a no-op command, since the command key is empty.
, direction(d)
{
}

DirectionalCommand::~DirectionalCommand()
{
}

Direction DirectionalCommand::get_direction() const
{
  return direction;
}

// Movement
MovementCommand::MovementCommand(const Direction d)
: DirectionalCommand(d)
{
  // Get the direction CommandKey based on the Direction enum
  string name  = DirectionEnum::to_string(direction);
  command_name = name;
}

MovementCommand::~MovementCommand()
{
}

// Move up or down a level
MoveUpLevelCommand::MoveUpLevelCommand()
: Command(CommandKeys::MOVE_UP)
{
}

MoveUpLevelCommand::~MoveUpLevelCommand()
{
}

MoveDownLevelCommand::MoveDownLevelCommand()
: Command(CommandKeys::MOVE_DOWN)
{
}

MoveDownLevelCommand::~MoveDownLevelCommand()
{
}

// Search
SearchCommand::SearchCommand()
: Command(CommandKeys::SEARCH)
{
}

SearchCommand::~SearchCommand()
{
}
