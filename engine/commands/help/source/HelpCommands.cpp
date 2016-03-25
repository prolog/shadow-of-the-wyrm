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

IntroductionRoguelikesCommand::IntroductionRoguelikesCommand(const int key)
: Command(HelpCommandKeys::INTRODUCTION_ROGUELIKES, key)
{
}

SOTWHistoryCommand::SOTWHistoryCommand(const int key)
  : Command(HelpCommandKeys::SOTW_HISTORY, key)
{
}