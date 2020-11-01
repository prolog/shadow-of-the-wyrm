#pragma once
#ifdef _MSC_VER
#include <curses.h>
#else
  #ifndef NCURSES_OPAQUE
    constexpr auto NCURSES_OPAQUE = 0;
  #endif
#include <ncurses.h>
#endif
