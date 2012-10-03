#include "CursesKeyboardController.hpp"
#include "CursesPromptProcessor.hpp"

using namespace std;

// Important: this currently only works on STDSCR!  If the general keyboard controller needs a particular window,
// extra code will be needed.
string CursesKeyboardController::get_line()
{
  CursesPromptProcessor ncpp;
  return ncpp.get_user_string(stdscr);
}

int CursesKeyboardController::get_char_as_int()
{
  int character = getch();
  return character;
}
