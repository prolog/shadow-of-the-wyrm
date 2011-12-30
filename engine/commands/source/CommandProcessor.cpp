#include "CommandKeys.hpp"
#include "CommandProcessor.hpp"
#include "Game.hpp"

using namespace std;

CommandProcessor::CommandProcessor()
{
}

CommandProcessor::~CommandProcessor()
{
}

// Process the Command
void CommandProcessor::process(CommandPtr command)
{
  if (command)
  {
    Game* game = Game::instance();
    string command_name = command->get_name();

    if (command_name == CommandKeys::QUIT)
    {
      game->quit();
    }
  }
}
