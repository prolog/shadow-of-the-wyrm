#include "HelpCommands.hpp"
#include "HelpCommandKeys.hpp"

using namespace std;

KeybindingsCommand::KeybindingsCommand(const int key)
: Command(HelpCommandKeys::KEYBINDINGS, key)
{
}

ExitHelpCommand::ExitHelpCommand(const int key)
: Command(HelpCommandKeys::EXIT_HELP, key)
{
}

