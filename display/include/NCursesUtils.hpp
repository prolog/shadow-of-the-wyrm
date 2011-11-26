#pragma once
#include <string>

class NCursesMenuUtils
{
  public:
    static std::string get_first_menu_selection_shortcut();
    static std::string get_last_menu_selection_shortcut();
    static std::string get_next_menu_selection_shortcut(const char* current_value);
};
