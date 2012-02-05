#pragma once
#include <ncurses.h>
#include "Controller.hpp"

class NCursesKeyboardController : public Controller
{
  public:
    std::string get_line();
    int get_char_as_int();
};
