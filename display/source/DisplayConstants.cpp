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

// The map always (always!) starts on row 2.  The message buffer
// always (always!) gets line 0 and 1.
const unsigned int DisplayConstants::MAP_START_ROW = 2;
const unsigned int DisplayConstants::MAP_START_COL = 0;
const unsigned int DisplayConstants::MESSAGE_BUFFER_END_ROW = 1;
const unsigned int DisplayConstants::MESSAGE_BUFFER_ROWS = 2;
