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

// Movement
MovementCommand::MovementCommand(const Direction direction)
: Command(CommandKeys::MOVE_NORTHEAST)
{
  // Get the direction CommandKey based on the Direction enum
  string name  = DirectionEnum::to_string(direction);
  command_name = name;
}

MovementCommand::~MovementCommand()
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
