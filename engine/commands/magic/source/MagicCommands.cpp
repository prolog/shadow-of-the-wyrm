#include "MagicCommands.hpp"
#include "MagicCommandKeys.hpp"

using namespace std;
SpellCommand::SpellCommand(const int spell_idx, const int key)
: Command(MagicCommandKeys::SELECT_SPELL, key), spell_index(spell_idx)
{
}

// Select a spell from the list
SelectSpellCommand::SelectSpellCommand(const int spell_idx, const int key)
: SpellCommand(spell_idx, key)
{  
}

// Go to the next page of spells
NextPageMagicCommand::NextPageMagicCommand(const int key)
: Command(MagicCommandKeys::NEXT_PAGE, key)
{
}

// Go to the previous page of spells
PreviousPageMagicCommand::PreviousPageMagicCommand(const int key)
: Command(MagicCommandKeys::PREVIOUS_PAGE, key)
{
}

// Exit back to the regular map view.
ExitMagicCommand::ExitMagicCommand(const int key)
: Command(MagicCommandKeys::EXIT_MAGIC, key)
{
}
