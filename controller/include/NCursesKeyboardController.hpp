#pragma once
#include <ncurses.h>
#include "Controller.hpp"

class NCursesKeyboardController : public Controller
{
  public:
    std::string get_line();
    char get_character();
};
