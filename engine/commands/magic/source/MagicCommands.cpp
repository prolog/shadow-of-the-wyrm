#include "MagicCommands.hpp"
#include "MagicCommandKeys.hpp"

using namespace std;

// Select a spell from the list
SelectSpellCommand::SelectSpellCommand()
: Command(MagicCommandKeys::SELECT_SPELL)
{  
}

// Go to the next page of spells
NextPageMagicCommand::NextPageMagicCommand()
: Command(MagicCommandKeys::NEXT_PAGE)
{
}

// Go to the previous page of spells
PreviousPageMagicCommand::PreviousPageMagicCommand()
: Command(MagicCommandKeys::PREVIOUS_PAGE)
{
}

// Exit back to the regular map view.
ExitMagicCommand::ExitMagicCommand()
: Command(MagicCommandKeys::EXIT_MAGIC)
{
}
