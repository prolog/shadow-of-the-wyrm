#pragma once
#ifdef _MSC_VER
#include <curses.h>
#else
#include <ncurses.h>
#endif

#include "Controller.hpp"

class CursesKeyboardController : public Controller
{
  public:
    std::string get_line();
    int get_char_as_int();

    virtual Controller* clone();

  private:
    ClassIdentifier internal_class_identifier() const override;
};
