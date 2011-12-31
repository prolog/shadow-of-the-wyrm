#include <boost/make_shared.hpp>
#include "CommandKeys.hpp"
#include "CommandProcessor.hpp"
#include "Commands.hpp"
#include "Game.hpp"

using namespace std;

CommandProcessor::CommandProcessor()
{
}

CommandProcessor::~CommandProcessor()
{
}

// Determine the type of command, and process it appropriately.
void CommandProcessor::process(CreaturePtr creature, CommandPtr command)
{
  if (command)
  {
    Command* raw_command = command.get();

    DirectionalCommand* d_command = dynamic_cast<DirectionalCommand*>(raw_command);

    if (d_command)
    {
      process_directional_command(creature, d_command);
    }
    else
    {
      // It's a subclass of the basic command, but not one of the subclasses requiring special processing.
      process_command(creature, raw_command);
    }
  }
}

// Process the Command
void CommandProcessor::process_command(CreaturePtr creature, Command* command)
{
  if (command)
  {
    Game* game = Game::instance();
    string command_name = command->get_name();

    if (command_name == CommandKeys::QUIT)
    {
      game->quit();
    }
    else if (command_name == CommandKeys::VERSION)
    {
      game->actions.version();
    }
    else if (command_name == CommandKeys::SEARCH)
    {
      game->actions.search(creature);
    }
  }
}

// Process the DirectionalCommand
void CommandProcessor::process_directional_command(CreaturePtr creature, DirectionalCommand* command)
{
  if (command)
  {
    Game* game = Game::instance();
    string command_name = command->get_name();

    if (CommandKeys::is_movement_type_key(command_name))
    {
      Direction movement_direction = command->get_direction();

      game->actions.move(creature, movement_direction);
    }
  }
}
