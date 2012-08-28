#include "NCursesKeyboardController.hpp"
#include "NCursesPromptProcessor.hpp"

using namespace std;

// Important: this currently only works on STDSCR!  If the general keyboard controller needs a particular window,
// extra code will be needed.
string NCursesKeyboardController::get_line()
{
  NCursesPromptProcessor ncpp;
  return ncpp.get_user_string(stdscr);
}

int NCursesKeyboardController::get_char_as_int()
{
  int character = getch();
  return character;
}
