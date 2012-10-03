#include "CursesUtils.hpp"

using namespace std;

string CursesMenuUtils::get_first_menu_selection_shortcut()
{
  string first = "a";
  return first;
}

string CursesMenuUtils::get_last_menu_selection_shortcut()
{
  string last = "z";
  return last;
}

string CursesMenuUtils::get_next_menu_selection_shortcut(const char* cur)
{
  string result;

  if (cur)
  {
    char next_value = cur[0];
    next_value++;

    // "*" has special meaning for menus - if available, it means to
    // select any of the options, randomly.  So don't allow it.
    if (next_value == '*')
    {
      next_value++;
    }

    result = next_value;
  }

  return result;
}
