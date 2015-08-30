#pragma once
#include <string>
#include <utility>

// The first eight are the same as the COLOR_ (American spelling) values
// in curses.h.  Consistency is nice.  The rest are just attributes on
// the standard 16 Curses colours.
enum struct Colours
{
  COLOUR_UNDEFINED = -1,
  COLOUR_BLACK = 0,
  COLOUR_RED = 1,
  COLOUR_GREEN = 2,
  COLOUR_YELLOW = 3,
  COLOUR_BLUE = 4,
  COLOUR_MAGENTA = 5,
  COLOUR_CYAN = 6,
  COLOUR_WHITE = 7,
  COLOUR_BOLD_BLACK = 8,
  COLOUR_BOLD_RED = 9,
  COLOUR_BOLD_GREEN = 10,
  COLOUR_BOLD_YELLOW = 11,
  COLOUR_BOLD_BLUE = 12,
  COLOUR_BOLD_MAGENTA = 13,
  COLOUR_BOLD_CYAN = 14,
  COLOUR_BOLD_WHITE = 15
};

using Colour = Colours;
using TextColour = std::pair<std::string, Colour>;