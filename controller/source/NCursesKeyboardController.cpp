#include "NCursesKeyboardController.hpp"

using namespace std;

string NCursesKeyboardController::get_line()
{
  char line_char[1000];
  getnstr(line_char, 1000);

  string line = line_char;
  return line;
}

int NCursesKeyboardController::get_char_as_int()
{
  int character = getch();
  return character;
}
