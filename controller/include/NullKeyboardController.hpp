#pragma once
#include "Controller.hpp"

// Because non-player-controlled creatures shouldn't need to get keyboard input, a simple
// class is defined that returns default values.
class NullKeyboardController : public Controller
{
  public:
    std::string get_line();
    int get_char_as_int();
};
