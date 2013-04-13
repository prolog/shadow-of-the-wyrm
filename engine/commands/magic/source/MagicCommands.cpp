#include "MagicCommands.hpp"
#include "MagicCommandKeys.hpp"

using namespace std;
SpellCommand::SpellCommand(const int spell_idx)
: Command(MagicCommandKeys::SELECT_SPELL), spell_index(spell_idx)
{
}

// Select a spell from the list
SelectSpellCommand::SelectSpellCommand(const int spell_idx)
: SpellCommand(spell_idx)
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
