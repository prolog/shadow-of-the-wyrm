#include "DisplayConstants.hpp"

using namespace std;

// Display identifiers.  These refer to "types" of display - curses, SDL,
// and so on.
const string DisplayIdentifier::DISPLAY_IDENTIFIER_CURSES = "curses";
const string DisplayIdentifier::DISPLAY_IDENTIFIER_SDL = "sdl";

DisplayIdentifier::DisplayIdentifier()
{
}

// Display constants
const int DisplayConstants::OPTION_SPACING = 1;
const int DisplayConstants::ROWS_FOR_MESSAGE_BUFFER_AND_SYNOPSIS = 5;